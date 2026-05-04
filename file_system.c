#include <stdio.h>
#include <string.h>
#include "file_system.h"

typedef struct {
    char name[50];
    int score;
} Player;

void saveScore(char playerName[], int newScore) {
    FILE *file = fopen("scores.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char name[50];
    int score;
    int found = 0;

    if (file != NULL) {
        while (fscanf(file, "%[^-] - Score: %d\n", name, &score) == 2) {
            
            // remove trailing space from name
            name[strcspn(name, "\n")] = 0;

            if (strcmp(name, playerName) == 0) {
                score += newScore;  // ✅ ADD scores
                fprintf(temp, "%s - Score: %d\n", name, score);
                found = 1;
            } else {
                fprintf(temp, "%s - Score: %d\n", name, score);
            }
        }
        fclose(file);
    }

    // If player not found → add new
    if (!found) {
        fprintf(temp, "%s - Score: %d\n", playerName, newScore);
    }

    fclose(temp);

    // Replace old file with updated one
    remove("scores.txt");
    rename("temp.txt", "scores.txt");
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

void resetLeaderboard() {
    FILE *file = fopen("scores.txt", "w"); // "w" clears the file
    if (file != NULL) {
        fclose(file);
        printf("Leaderboard has been reset!\n");
    } else {
        printf("Error resetting leaderboard.\n");
    }
}