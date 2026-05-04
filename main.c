#include <stdio.h>
#include "games.h"
#include "quiz.h"
#include "file_system.h"

// Function declarations
void showMenu();
char playerName[50];

int main() {
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
                printf("Stories section coming soon...\n\n");
                break;

            case 2:
                playNumberGame();
                break;

            case 3:
            startQuiz();
            break;

            case 4:
            showLeaderboard();
            break;

            case 5:
                printf("Exiting... Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n\n");
        }

    } while(choice != 5);

    return 0;
}

// Menu function
void showMenu() {
    printf("\n===== Kids Magazine =====\n");
    printf("1. Stories\n");
    printf("2. Games\n");
    printf("3. Quiz\n");
    printf("4. Leaderboard\n");
    printf("5. Exit\n");
    printf("=========================\n");
}