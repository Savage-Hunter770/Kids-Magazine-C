#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "games.h"
#include "file_system.h"

extern char playerName[50];

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

const char* getChoiceName(int choice) {
    if (choice == 1) return "Rock";
    if (choice == 2) return "Paper";
    if (choice == 3) return "Scissors";
    return "Unknown";
}

void countdown() {
    printf("\nGet ready...\n");
    Sleep(500);
    printf("3...\n"); Sleep(500);
    printf("2...\n"); Sleep(500);
    printf("1...\n"); Sleep(500);
    printf("GO!\n\n");
}

void playRPS() {
    int user, computer;
    char again;
    int wins = 0, losses = 0, draws = 0, score = 0;
    int rounds = 0;

    do {
        printf("\n🎮 Rock Paper Scissors (Best of 3) 🎮\n");

        while (wins < 2 && losses < 2) {
            printf("\n1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter your choice: ");
            scanf("%d", &user);

            countdown();

            computer = rand() % 3 + 1;

            printf("You chose: %s\n", getChoiceName(user));
            printf("Computer chose: %s\n", getChoiceName(computer));

            if (user == computer) {
                printf("It's a draw!\n");
                draws++;
            } 
            else if ((user == 1 && computer == 3) ||
                     (user == 2 && computer == 1) ||
                     (user == 3 && computer == 2)) {
                printf("You win this round!\n");
                wins++;
                score++;
            } 
            else {
                printf("You lose this round!\n");
                losses++;
                score--;
            }

            rounds++;

            printf("Score → You: %d | Computer: %d | Draws: %d\n",
                   wins, losses, draws);
        }

        if (wins == 2)
            printf("\n🏆 You WON the match!\n");
        else
            printf("\n💀 You LOST the match!\n");

        printf("\nPlay again? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    saveScore(playerName, score);
    printf("Score updated in leaderboard!\n");
}