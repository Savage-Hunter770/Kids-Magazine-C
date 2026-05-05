#include <stdio.h>      // Provides input/output functions like printf() and scanf()

#include <string.h>     // Provides string handling functions like strcmp(), strlen(), strcspn()

#include "file_system.h" // Includes custom function declarations (e.g., saveScore, showLeaderboard)

// ===================== SAVE / UPDATE PLAYER SCORE =====================
// This function updates the player's score in "scores.txt".
// If the player exists → their score is increased.
// If the player does not exist → a new entry is created.
// Uses a temporary file to safely rewrite updated data.

void saveScore(char playerName[], int newScore) {

    // Open the original scores file in READ mode
    FILE *file = fopen("scores.txt", "r");

    // Open a temporary file in WRITE mode (used to store updated data)
    FILE *temp = fopen("temp.txt", "w");

    // Variables to store data read from file
    char name[50];   // player name from file
    int score;       // player score from file

    int found = 0;   // flag → checks if player already exists (0 = not found)

    // If file exists, start reading it line by line
    if (file != NULL) {

        // Read each line in format: "Name - Score: X"
        // %49[^-] → read name until '-' (prevents overflow)
        // %d → read score
        while (fscanf(file, "%49[^-] - Score: %d\n", name, &score) == 2) {
            
            // ---------------- CLEAN NAME ----------------

            // Remove newline character if present
            name[strcspn(name, "\n")] = 0;

            // Remove trailing spaces at the end of the name
            int len = strlen(name);
            while (len > 0 && name[len - 1] == ' ') {
                name[len - 1] = '\0';  // cut last character
                len--;
            }

            // ---------------- CHECK PLAYER ----------------

            // Compare file name with current player name
            if (strcmp(name, playerName) == 0) {

                // Player found → update score
                score += newScore;

                // Write updated score to temp file
                fprintf(temp, "%s - Score: %d\n", name, score);

                found = 1; // mark as found
            } 
            else {
                // Other players → copy data as-is
                fprintf(temp, "%s - Score: %d\n", name, score);
            }
        }

        // Close original file after reading
        fclose(file);
    }

    // ---------------- ADD NEW PLAYER ----------------

    // If player was not found in file → create new entry
    if (!found) {
        fprintf(temp, "%s - Score: %d\n", playerName, newScore);
    }

    // Close temporary file after writing
    fclose(temp);

    // ---------------- REPLACE OLD FILE ----------------

    // Delete original file
    remove("scores.txt");

    // Rename temp file → becomes the new scores file
    rename("temp.txt", "scores.txt");
}

// ===================== SHOW LEADERBOARD =====================
// This function reads all player scores from "scores.txt"
// and displays them line by line on the screen.
// If the file does not exist, it informs the user.

void showLeaderboard() {

    // Open the scores file in READ mode
    FILE *file = fopen("scores.txt", "r");

    // Check if file failed to open (does not exist or error)
    if (file == NULL) {
        printf("No scores available yet!\n");
        return; // exit function early
    }

    // Buffer to store one line from the file
    char line[100];

    // Print leaderboard header
    printf("\n===== Leaderboard =====\n");

    // Read file line by line until end of file
    while (fgets(line, sizeof(line), file)) {

        // Print each line exactly as stored in the file
        printf("%s", line);
    }

    // Print leaderboard footer
    printf("=======================\n");

    // Close the file after reading
    fclose(file);
}

// ===================== RESET LEADERBOARD =====================
// This function clears all data inside "scores.txt".
// It opens the file in write mode ("w"), which automatically
// deletes all existing content. Then it closes the file and
// informs the user whether the operation was successful.

void resetLeaderboard() {

    // Open the scores file in WRITE mode
    // "w" → clears the file if it exists, or creates a new one
    FILE *file = fopen("scores.txt", "w");

    // Check if file was opened successfully
    if (file != NULL) {

        // Close the file after clearing it
        fclose(file);

        // Inform the user that reset was successful
        printf("Leaderboard has been reset!\n");
    } 
    else {
        // If file could not be opened, display error message
        printf("Error resetting leaderboard.\n");
    }
}

// ===================== GET PLAYER SCORE =====================
// This function searches for a player in "scores.txt" and returns their score.
// If the player is found → return their score.
// If the player is NOT found or file doesn't exist → return 0.

int getPlayerScore(char playerName[]) {

    // Open the scores file in READ mode
    FILE *file = fopen("scores.txt", "r");

    // If file does not exist or failed to open
    if (file == NULL) {
        return 0; // no score available
    }

    // Variables to store data read from file
    char name[50]; // stores player name from file
    int score;     // stores player score from file

    // Read file line by line in format: "Name - Score: X"
    // Loop continues while fscanf successfully reads name and score
    while (fscanf(file, "%[^-] - Score: %d\n", name, &score) == 2) {
        
        // ---------------- CLEAN NAME ----------------

        // Remove trailing space caused by format reading (before '-')
        name[strcspn(name, " ")] = '\0';

        // ---------------- CHECK PLAYER ----------------

        // Compare current name with target player name
        if (strcmp(name, playerName) == 0) {

            // Close file before returning (good practice)
            fclose(file);

            // Return the found score
            return score;
        }
    }

    // Close file after finishing reading
    fclose(file);

    // Player not found → return 0
    return 0;
}