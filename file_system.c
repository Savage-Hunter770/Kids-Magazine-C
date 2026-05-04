#include <stdio.h>
#include "file_system.h"

void saveScore(char name[], int score) {
    FILE *file = fopen("scores.txt", "a");

    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s - Score: %d\n", name, score);
    fclose(file);

    printf("Score saved successfully!\n");
}

void showLeaderboard() {
    FILE *file = fopen("scores.txt", "r");

    if(file == NULL) {
        printf("No scores available yet!\n");
        return;
    }

    char line[100];

    printf("\n===== Leaderboard =====\n");

    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("=======================\n");

    fclose(file);
}