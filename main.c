#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "games.h"
#include "quiz.h"
#include "file_system.h"
#include "story.h"

// Function declarations
void showMenu();
char playerName[50];

int main() {
    srand(time(0));

    printf("Enter your name: ");
    scanf("%s", playerName);

    printf("\n==============================\n");
    printf(" Welcome %s to Kids Magazine!\n", playerName);
    printf("==============================\n\n");

    int choice;

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                startStory();
                break;

            case 2: {
                int gameChoice;

                printf("\nChoose a game:\n");
                printf("1. Number Guessing\n");
                printf("2. Rock Paper Scissors\n");

                scanf("%d", &gameChoice);

                if (gameChoice == 1) {
                    playNumberGame();
                } else if (gameChoice == 2) {
                    playRPS();
                } else {
                    printf("Invalid choice!\n");
                }

                break;
            }

            case 3:
            startQuiz();
            break;

            case 4:
            showLeaderboard();
            break;

            case 5: {
                char confirm;

                printf("⚠️ Are you sure you want to reset the leaderboard? (y/n): ");
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y') {
                    resetLeaderboard();
                } else {
                    printf("Reset cancelled.\n");
                }

                break;
        }

                case 6:
                    printf("Exiting... Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n\n");
        }

    } while(choice != 6);

    return 0;
}

// Menu function
void showMenu() {
    printf("\n===== Kids Magazine =====\n");
    printf("1. Stories\n");
    printf("2. Games\n");
    printf("3. Quiz\n");
    printf("4. Leaderboard\n");
    printf("5. Reset Leaderboard\n");
    printf("6. Exit\n"); 
    printf("=========================\n");
}