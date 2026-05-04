#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "games.h"

void playNumberGame() {
    int number, guess;

    srand(time(0));
    number = rand() % 10 + 1;

    printf("\n🎮 Number Guessing Game 🎮\n");
    printf("Guess a number between 1 and 10:\n");

    do {
        scanf("%d", &guess);

        if (guess > number)
            printf("Too high! Try again:\n");
        else if (guess < number)
            printf("Too low! Try again:\n");
        else
            printf("Correct! 🎉\n");

    } while (guess != number);
}