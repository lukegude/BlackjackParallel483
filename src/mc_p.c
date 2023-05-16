#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "blackjack.h"

#define SIM_COUNT 1000000

float thread_comparison(int num_simulations){
    double start_time, end_time;
    int wins = 0, draws = 0, losses = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+ : wins) reduction(+ : draws) reduction(+ : losses)
    for (int i = 0; i < num_simulations; i++)
    {
        int result = play_blackjack_strategy(basic_strategy);
        if (result == 1)
            wins++;
        else if (result == 0)
            draws++;
        else
            losses++;
    }
    end_time = omp_get_wtime();
    return (end_time - start_time);
}



void run_full_simulation(int num_simulations)
{
    int wins = 0, draws = 0, losses = 0;
    double start_time, end_time;

    FILE *fp = fopen("mc_p.txt", "a");
    start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : wins) reduction(+ : draws) reduction(+ : losses)
    for (int i = 0; i < num_simulations; i++)
    {
        int result = play_blackjack_strategy(basic_strategy);
        if (result == 1)
            wins++;
        else if (result == 0)
            draws++;
        else
            losses++;
    }
    end_time = omp_get_wtime();
    printf("\n------BASIC STRATEGY------\n");
    printf("Time taken: %.2fs\n", (end_time - start_time));

    printf("Results after %d simulations:\n", num_simulations);
    printf("Wins: %d (%.2f%%)\n", wins, (double)wins / num_simulations * 100);
    printf("Draws: %d (%.2f%%)\n", draws, (double)draws / num_simulations * 100);
    printf("Losses: %d (%.2f%%)\n", losses, (double)losses / num_simulations * 100);

    fprintf(fp, "%f %d %d %d %d\n", (end_time - start_time), num_simulations, wins, draws, losses);

    wins = 0, draws = 0, losses = 0;

    start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : wins) reduction(+ : draws) reduction(+ : losses)
    for (int i = 0; i < num_simulations; i++)
    {
        int result = play_blackjack_strategy(aggressive_strategy);
        if (result == 1)
            wins++;
        else if (result == 0)
            draws++;
        else
            losses++;
    }
    end_time = omp_get_wtime();
    printf("\n------AGRESSIVE STRATEGY------\n");
    printf("Time taken: %.2fs\n", (end_time - start_time));

    printf("Results after %d simulations:\n", num_simulations);
    printf("Wins: %d (%.2f%%)\n", wins, (double)wins / num_simulations * 100);
    printf("Draws: %d (%.2f%%)\n", draws, (double)draws / num_simulations * 100);
    printf("Losses: %d (%.2f%%)\n", losses, (double)losses / num_simulations * 100);

    fprintf(fp, "%f %d %d %d %d\n", (end_time - start_time), num_simulations, wins, draws, losses);

    wins = 0, draws = 0, losses = 0;

    start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : wins) reduction(+ : draws) reduction(+ : losses)
    for (int i = 0; i < num_simulations; i++)
    {
        int result = play_blackjack_strategy(conservative_strategy);
        if (result == 1)
            wins++;
        else if (result == 0)
            draws++;
        else
            losses++;
    }
    end_time = omp_get_wtime();
    printf("\n------CONSERVATIVE STRATEGY------\n");
    printf("Time taken: %.2fs\n", (end_time - start_time));

    printf("Results after %d simulations:\n", num_simulations);
    printf("Wins: %d (%.2f%%)\n", wins, (double)wins / num_simulations * 100);
    printf("Draws: %d (%.2f%%)\n", draws, (double)draws / num_simulations * 100);
    printf("Losses: %d (%.2f%%)\n", losses, (double)losses / num_simulations * 100);

    fprintf(fp, "%f %d %d %d %d\n", (end_time - start_time), num_simulations, wins, draws, losses);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <number_of_simulations>\n", argv[0]);
        exit(1);
    }
    if (argc == 3) // Number of threads specified
    {
        omp_set_num_threads(atoi(argv[2]));
    }
    //run_full_simulation(atoi(argv[1]));
    FILE *fp = fopen("mc_p.txt", "a");
    fprintf(fp, "%f %d %d\n", thread_comparison(atoi(argv[1])), atoi(argv[1]), atoi(argv[2]));
    fclose(fp);


    return 0;
}
