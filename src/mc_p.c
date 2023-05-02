#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "blackjack.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_simulations>\n", argv[0]);
        exit(1);
    }

    int num_simulations = atoi(argv[1]);
    int wins = 0, draws = 0, losses = 0;
    double start_time, end_time;

    srand(time(NULL));
    start_time = clock();
    #pragma omp parallel for reduction(+:wins) reduction(+:draws) reduction(+:losses)
    for (int i = 0; i < num_simulations; i++) {
        int result = play_blackjack_strategy(basic_strategy);
        if (result == 1) wins++;
        else if (result == 0) draws++;
        else losses++;
    }
    end_time = clock();
    printf("Time taken: %.2fs\n", (end_time - start_time) / CLOCKS_PER_SEC);

    printf("Results after %d simulations:\n", num_simulations);
    printf("Wins: %d (%.2f%%)\n", wins, (double)wins / num_simulations * 100);
    printf("Draws: %d (%.2f%%)\n", draws, (double)draws / num_simulations * 100);
    printf("Losses: %d (%.2f%%)\n", losses, (double)losses / num_simulations * 100);

    return 0;
}

