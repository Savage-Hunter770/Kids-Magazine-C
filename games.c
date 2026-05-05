#include <stdio.h>      // for printf and scanf (input/output)
#include <stdlib.h>     // for rand(), srand()
#include <time.h>       // for time(0) (used to randomize numbers)
#include <windows.h>    // for Sleep() function (delay)
#include "games.h"      // header for this file (function declarations)
#include "file_system.h"    // for saveScore()

// This variable is defined in main.c, we use it here to save scores with the player's name
extern char playerName[50];


// ===================== INPUT VALIDATION =====================
// This function makes sure user enters a VALID number between min and max
int getValidChoice(int min, int max) {
    int choice; // stores user input
    int result; // stores result of scanf

    while (1) { // infinite loop until valid input is entered

        result = scanf("%d", &choice);  // try reading an integer

        // WRONG! If user enters something NOT a number (like text)
        if (result != 1) {
            printf("Invalid input! Enter a number.\n");

            while (getchar() != '\n'); // clear bad input from buffer
        }
        // Wrong! If number is outside allowed range
        else if (choice < min || choice > max) {
            printf("Invalid choice! Enter between %d and %d.\n", min, max);
        }
        // Valid input
        else {
            return choice; // exit function and return value
        }
    }
}


// ===================== NUMBER GUESSING GAME =====================
void playNumberGame() {
    int number, guess;     // number = random number, guess = user input
    int difficulty;        // stores difficulty level
    int maxRange, attempts; // range and allowed tries
    int tries = 0;         // how many guesses user made
    int score = 0;         // player score

    // Initialize random generator
    srand(time(0));

    printf("\n** Number Guessing Game **\n");

    // Ask for difficulty
    printf("\nSelect Difficulty:\n");
    printf("1. EASY (Unlimited Tries)\n2. MEDIUM (10 Tries)\n3. HARD (7 Tries)\n");

    difficulty = getValidChoice(1, 3); // safe input

    // Set difficulty rules
    if (difficulty == 1) {
        maxRange = 10;   // numbers from 1–10
        attempts = -1;   // unlimited attempts
    }
    else if (difficulty == 2) {
        maxRange = 50;   // numbers from 1–50
        attempts = 10;   // max 10 tries
    }
    else {
        maxRange = 100;  // numbers from 1–100
        attempts = 7;    // max 7 tries
    }

    // Generate random number between 1 and maxRange
    number = rand() % maxRange + 1;

    printf("\nGuess a number from 1 to %d:\n", maxRange);

    // Game loop
    while (1) {
        guess = getValidChoice(1, maxRange); // safe guess
        tries++; // increase tries count

        // Too high
        if (guess > number)
            printf("Too high! Try again:\n");

        // Too low
        else if (guess < number)
            printf("Too low! Try again:\n");

            // Correct guess
        else {
            printf("Correct!\n");

            // BASE SCORE depends on difficulty
            if (difficulty == 1) score = 1;
            else if (difficulty == 2) score = 2;
            else score = 3;

            // Bonus: fewer tries = more reward
            if (tries <= 3) score += 1;

            printf("You earned %d points!\n", score);

            // Save score to file_system.c
            saveScore(playerName, score);
            printf("Score updated in leaderboard!\n");

            break; // exit loop and end game
        }

        // Show remaining attempts (if limited mode)
        if (attempts != -1) {
            printf("Attempts left: %d\n", attempts - tries);
        }

        // Game over condition
        if (attempts != -1 && tries >= attempts) {
            printf("Game Over! The number was %d\n", number);
            break;
        }
    }
}


// ===================== RPS HELPER FUNCTIONS =====================

// Converts number → text
const char* getChoiceName(int choice) {
    if (choice == 1) return "Rock";
    if (choice == 2) return "Paper";
    if (choice == 3) return "Scissors";
    return "Unknown"; // should never happen
}

// Adds dramatic countdown effect before revealing choices
void countdown() {
    printf("\nGet ready...\n");

    Sleep(500); // wait 0.5 seconds
    printf("3...\n"); 
    
    Sleep(500);
    printf("2...\n"); 
    
    Sleep(500);
    printf("1...\n"); 
    
    Sleep(500);
    printf("GO!\n\n");
}


// ===================== ROCK PAPER SCISSORS GAME =====================
void playRPS() {
    int user, computer; // player choice and computer choice
    char again;         // play again input
    int score = 0;      // total score across matches

    // Outer loop → replay game
    do {
        int wins = 0, losses = 0, draws = 0;

        printf("\n** Rock Paper Scissors (Best of 3) **\n");

        // Match loop → first to 2 wins
        while (wins < 2 && losses < 2) {

            // Show options
            printf("\n1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter your choice: ");

            user = getValidChoice(1, 3); // safe input

            countdown(); // visual effect

            // Random computer choice
            computer = rand() % 3 + 1;

            // Show choices
            printf("You chose: %s\n", getChoiceName(user));
            printf("Computer chose: %s\n", getChoiceName(computer));

            // Draw
            if (user == computer) {
                printf("It's a draw!\n");
                draws++;
            } 

            // Win conditions
            else if ((user == 1 && computer == 3) ||
                     (user == 2 && computer == 1) ||
                     (user == 3 && computer == 2)) {
                printf("You win this round!\n");
                wins++;
                score++; // increase score for wins
            } 

            // Lose condition
            else {
                printf("You lose this round!\n");
                losses++;
                score--; // decrease score for losses
            }

            // Show current match status
            printf("Score → You: %d | Computer: %d | Draws: %d\n",
                   wins, losses, draws);
        }

        // Match result
        if (wins == 2)
            printf("\nYou WON the match!\n");
        else
            printf("\nYou LOST the match!\n");

        // Validate replay input
        do {
            printf("\nPlay again? (y/n): ");
            scanf(" %c", &again); // space before %c to consume leftover newline

            if (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                printf("Invalid choice! Enter y or n.\n");
            }

        } while (again != 'y' && again != 'Y' && again != 'n' && again != 'N');

    } while (again == 'y' || again == 'Y');

     // Save total score after all matches
    saveScore(playerName, score);
    printf("Score updated in leaderboard!\n");
}