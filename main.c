#include <stdio.h>

// Function declarations
void showMenu();

int main() {
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
                printf("Games section coming soon...\n\n");
                break;

            case 3:
                printf("Quiz section coming soon...\n\n");
                break;

            case 4:
                printf("Exiting... Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n\n");
        }

    } while(choice != 4);

    return 0;
}

// Menu function
void showMenu() {
    printf("===== Kids Magazine =====\n");
    printf("1. Stories\n");
    printf("2. Games\n");
    printf("3. Quiz\n");
    printf("4. Exit\n");
}