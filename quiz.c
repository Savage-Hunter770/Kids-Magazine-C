#include <stdio.h>      // for printf and scanf (input/output)
#include <string.h>     // for string functions (not heavily used here)

#include "quiz.h"       // allows main.c to call startQuiz()
#include "file_system.h"// allows saving and retrieving scores

// This variable is defined in main.c, we are using it here
extern char playerName[50];

// ---------------- STRUCT DEFINITION ----------------
// This defines what a "Question" looks like
struct Question {
    char question[100];      // stores the question text
    char options[4][50];     // stores 4 possible answers (each is a string)
    int correct;             // stores index of correct answer (0 to 3)
};

// ---------------- MAIN QUIZ FUNCTION ----------------
void startQuiz() {
    int difficulty; // stores user's difficulty choice

    // Ask user to choose difficulty
    printf("\nChoose difficulty:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n");
    scanf("%d", &difficulty);

    // ---------------- QUIZ DATA ----------------
    // 2D array:
    // 3 difficulties × 5 questions each
    struct Question quiz[3][5] = {

        // ---------------- EASY QUESTIONS ----------------
        {
            {"What color is the sky?",
             {"Blue", "Red", "Green", "Yellow"},
             0},

            {"How many legs does a dog have?",
             {"2", "3", "4", "5"},
             2},

            {"2 + 2 = ?",
             {"3", "4", "5", "6"},
             1},

            {"What sound does a cat make?",
             {"Bark", "Meow", "Roar", "Moo"},
             1},

            {"Which one is a fruit?",
             {"Carrot", "Potato", "Apple", "Onion"},
             2}
        },

        // ---------------- MEDIUM QUESTIONS ----------------
        {
            {"Which planet do we live on?",
             {"Mars", "Earth", "Venus", "Jupiter"},
             1},

            {"What is 12 * 2?",
             {"22", "24", "26", "20"},
             1},

            {"Which animal is king of the jungle?",
             {"Tiger", "Lion", "Elephant", "Bear"},
             1},

            {"What is the capital of France?",
             {"Rome", "Paris", "Berlin", "Madrid"},
             1},

            {"Which is a programming language?",
             {"HTML", "Python", "HTTP", "WiFi"},
             1}
        },

        // ---------------- HARD QUESTIONS ----------------
        {
            {"How many continents are there?",
             {"5", "6", "7", "8"},
             2},

            {"What gas do humans breathe in?",
             {"Oxygen", "Carbon Dioxide", "Nitrogen", "Helium"},
             0},

            {"7 * 8 + 2 = ?",
             {"54", "58", "60", "56"},
             1},

            {"Which ocean is the largest?",
             {"Atlantic", "Indian", "Pacific", "Arctic"},
             2},

            {"What is the square root of 64?",
             {"6", "7", "8", "9"},
             2}
        }
    };

    // ---------------- VARIABLES ----------------
    int score = 0;              // counts correct answers
    int answer;                 // stores user's answer
    int level = difficulty - 1; // convert 1–3 → 0–2 for array indexing

    // ---------------- VALIDATE DIFFICULTY ----------------
    if (level < 0 || level > 2) {
        printf("Invalid difficulty!\n");
        return; // stop the function if input is wrong
    }

    printf("\n--- Quiz Started ---\n");

    // ---------------- QUESTION LOOP ----------------
    // Loop through 5 questions for the chosen difficulty
    for (int i = 0; i < 5; i++) {
        printf("\nQ%d: %s\n", i + 1, quiz[level][i].question);

        // ---------------- OPTIONS LOOP ----------------
        // Loop through 4 options for the current question
        for (int j = 0; j < 4; j++) {

            // Print each option
            // j+1 makes numbering start from 1 instead of 0
            printf("%d. %s\n", j + 1, quiz[level][i].options[j]);
        }

        // Ask user for answer
        printf("Your answer: ");
        scanf("%d", &answer);

        // ---------------- CHECK ANSWER ----------------
        // answer - 1 converts user input (1–4) to index (0–3)
        if (answer - 1 == quiz[level][i].correct) {
            printf("Correct!\n");
            score++; // increase score if correct
        } else {
            printf("Wrong!\n");
        }
    }

    // ---------------- FINAL SCORE ----------------
    printf("\nYou scored: %d\n", score);

    // Save score to file_system.c
    saveScore(playerName, score);

    // Get updated total score from file_system.c and display it
    int total = getPlayerScore(playerName);

    // Display updated total score
    printf("Total Score Updated: %d\n", total);
}