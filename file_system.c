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