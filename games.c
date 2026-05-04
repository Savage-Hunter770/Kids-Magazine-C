#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "games.h"
#include "file_system.h"

extern char playerName[50];


// ===================== INPUT VALIDATION =====================
int getValidChoice(int min, int max) {
    int choice;
    int result;

    while (1) {
        result = scanf("%d", &choice);

        if (result != 1) {
            printf("Invalid input! Enter a number.\n");
            while (getchar() != '\n'); // clear buffer
        }
        else if (choice < min || choice > max) {
            printf("Invalid choice! Enter between %d and %d.\n", min, max);
        }
        else {
            return choice;
        }
    }
}


// ===================== NUMBER GAME =====================
void playNumberGame() {
    int number, guess;

    srand(time(0));
    number = rand() % 10 + 1;

    printf("\n🎮 Number Guessing Game 🎮\n");
    printf("Guess a number between 1 and 10:\n");

    do {
        guess = getValidChoice(1, 10);

        if (guess > number)
            printf("Too high! Try again:\n");
        else if (guess < number)
            printf("Too low! Try again:\n");
        else
            printf("Correct! 🎉\n");

    } while (guess != number);
}


// ===================== RPS HELPERS =====================
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


// ===================== ROCK PAPER SCISSORS =====================
void playRPS() {
    int user, computer;
    char again;
    int score = 0;   // total score across matches

    do {
        int wins = 0, losses = 0, draws = 0;

        printf("\n🎮 Rock Paper Scissors (Best of 3) 🎮\n");

        while (wins < 2 && losses < 2) {
            printf("\n1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter your choice: ");
            user = getValidChoice(1, 3);

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

            printf("Score → You: %d | Computer: %d | Draws: %d\n",
                   wins, losses, draws);
        }

        if (wins == 2)
            printf("\n🏆 You WON the match!\n");
        else
            printf("\n💀 You LOST the match!\n");

        // VALIDATE y/n INPUT
        do {
            printf("\nPlay again? (y/n): ");
            scanf(" %c", &again);

            if (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                printf("Invalid choice! Enter y or n.\n");
            }

        } while (again != 'y' && again != 'Y' && again != 'n' && again != 'N');

    } while (again == 'y' || again == 'Y');

    // Save final accumulated score
    saveScore(playerName, score);
    printf("Score updated in leaderboard!\n");
}