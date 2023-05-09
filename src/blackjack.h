#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52
#define NUM_HANDS 32
#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_UPCARDS 11

typedef enum {
    CLUBS, DIAMONDS, HEARTS, SPADES
} Suit;

typedef enum {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

typedef struct {
    Card cards[NUM_CARDS];
    int top;
} Deck;

typedef enum {
    HIT, STAND, DOUBLE_DOWN, SPLIT
} Action;

typedef Action (*StrategyFunc)(int player_total, int player_aces, int dealer_upcard_value);


Action basic_strategy(int player_total, int player_aces, int dealer_upcard_value);

Action lookup_table[NUM_HANDS][NUM_UPCARDS];

void generate_lookup_table() {
    #pragma omp parallel for
    for (int player_hand = 4; player_hand <= 20; ++player_hand) {
        for (int dealer_upcard = 2; dealer_upcard <= 11; ++dealer_upcard) {
            // Simulate or use a predefined rule to determine the best action
            // for each combination of player_hand and dealer_upcard.
            // This example uses a simple rule for illustration purposes.
            if (player_hand <= 11) {
                lookup_table[player_hand - 4][dealer_upcard - 2] = HIT;
            } else if (player_hand >= 17) {
                lookup_table[player_hand - 4][dealer_upcard - 2] = STAND;
            } else if (dealer_upcard <= 3) {
                lookup_table[player_hand - 4][dealer_upcard - 2] = STAND;
            } else {
                lookup_table[player_hand - 4][dealer_upcard - 2] = HIT;
            }
        }
    }
}


int play_blackjack_strategy(StrategyFunc strategy);

void init_deck(Deck* deck) {
    for (int i = 0; i < NUM_CARDS; i++) {
        deck->cards[i].suit = i / NUM_RANKS;
        deck->cards[i].rank = i % NUM_RANKS;
    }
    deck->top = 0;
}

void shuffle_deck(Deck* deck) {
    srand(time(NULL));
    for (int i = NUM_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
    deck->top = 0;
}

Card draw_card(Deck* deck) {
    return deck->cards[deck->top++];
}

Action basic_strategy(int player_total, int player_aces, int dealer_upcard_value) {
    if (player_aces > 0) { // Soft total
        if (player_total >= 19) return STAND;
        if (player_total == 18) {
            if (dealer_upcard_value >= 3 && dealer_upcard_value <= 6) return STAND;
            else return HIT;
        }
        if (player_total <= 17) return HIT;
    } else { // Hard total
        if (player_total >= 17) return STAND;
        if (player_total >= 13 && dealer_upcard_value >= 2 && dealer_upcard_value <= 6) return STAND;
        if (player_total == 12 && dealer_upcard_value >= 4 && dealer_upcard_value <= 6) return STAND;
        if (player_total <= 11) return HIT;
    }

    return HIT;
}


int card_value(Card card) {
    switch (card.rank) {
        case ACE:
            return 11;
        case KING:
        case QUEEN:
        case JACK:
        case TEN:
            return 10;
        default:
            return card.rank + 2;
    }
}

int play_blackjack_strategy(StrategyFunc strategy) {
    Deck deck;
    init_deck(&deck);
    shuffle_deck(&deck);

    Card player_cards[11];
    int player_count = 0;
    int player_total = 0;
    int player_aces = 0;

    Card dealer_cards[11];
    int dealer_count = 0;
    int dealer_total = 0;
    int dealer_aces = 0;

    // Initial draw
    for (int i = 0; i < 2; i++) {
        Card player_card = draw_card(&deck);
        player_cards[player_count++] = player_card;
        player_total += card_value(player_card);
        if (player_card.rank == ACE) player_aces++;

        Card dealer_card = draw_card(&deck);
        dealer_cards[dealer_count++] = dealer_card;
        dealer_total += card_value(dealer_card);
        if (dealer_card.rank == ACE) dealer_aces++;
    }

    // Player's turn
    while (player_total < 21) {
        Action action = strategy(player_total, player_aces, card_value(dealer_cards[1]));
        //Action action = lookup_table[player_total - 4][card_value(dealer_cards[1]) - 2];

        if (action == HIT) {
            Card player_card = draw_card(&deck);
            player_cards[player_count++] = player_card;
            player_total += card_value(player_card);
            if (player_card.rank == ACE) player_aces++;

            while (player_total > 21 && player_aces > 0) {
                player_total -= 10;
                player_aces--;
            }
        } else {
            break;
        }
    }

    // Dealer's turn
    while (dealer_total < 17) {
        Card dealer_card = draw_card(&deck);
        dealer_cards[dealer_count++] = dealer_card;
        dealer_total += card_value(dealer_card);
        if (dealer_card.rank == ACE) dealer_aces++;

        while (dealer_total > 21 && dealer_aces > 0) {
            dealer_total -= 10;
            dealer_aces--;
        }
    }

    // Return the result of the game: -1 = loss, 0 = draw, 1 = win
    if (player_total > 21) {
        return -1;
    } else if (dealer_total > 21 || player_total > dealer_total) {
        return 1;
    } else if (player_total == dealer_total) {
        return 0;
    } else {
        return -1;
    }
}

