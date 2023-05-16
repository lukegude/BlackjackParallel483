#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
Action basic_strategy(int player_total, int player_aces, int dealer_upcard_value);

void run_simulation(int num_simulations){
    int wins = 0, draws = 0, losses = 0;

    double start_time, end_time;
    srand(time(NULL));
    start_time = clock();
    for (int i = 0; i < num_simulations; i++) {
        int result = play_blackjack_strategy(basic_strategy);
        if (result == 1) wins++;
        else if (result == 0) draws++;
        else losses++;
    }
    end_time = clock();
    // printf("Time taken: %.2fs\n", (end_time - start_time) / CLOCKS_PER_SEC);
    // printf("Results after %d simulations:\n", num_simulations);
    // printf("Wins: %d (%.2f%%)\n", wins, (double)wins / num_simulations * 100);
    // printf("Draws: %d (%.2f%%)\n", draws, (double)draws / num_simulations * 100);
    // printf("Losses: %d (%.2f%%)\n", losses, (double)losses / num_simulations * 100);
    FILE *fp = fopen("mc_s.txt", "a");
    fprintf(fp, "%f %d %d %d %d\n", (end_time - start_time) / CLOCKS_PER_SEC ,num_simulations, wins, draws, losses);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_simulations>\n", argv[0]);
        exit(1);
    }
    run_simulation(atoi(argv[1]));


    return 0;
}

