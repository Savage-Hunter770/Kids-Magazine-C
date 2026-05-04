#include <stdio.h>
#include <string.h>
#include "quiz.h"
#include "file_system.h"

extern char playerName[50];

struct Question {
    char question[100];
    char options[4][50];
    int correct;
};

void startQuiz() {
    int difficulty;

    printf("\nChoose difficulty:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n");
    scanf("%d", &difficulty);

    struct Question quiz[3][5] = {

        // EASY
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

        // MEDIUM
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

        // HARD
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

    int score = 0;
    int answer;
    int level = difficulty - 1;

    if (level < 0 || level > 2) {
        printf("Invalid difficulty!\n");
        return;
    }

    printf("\n--- Quiz Started ---\n");

    for (int i = 0; i < 5; i++) {
        printf("\nQ%d: %s\n", i + 1, quiz[level][i].question);

        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, quiz[level][i].options[j]);
        }

        printf("Your answer: ");
        scanf("%d", &answer);

        if (answer - 1 == quiz[level][i].correct) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong!\n");
        }
    }

    printf("\nYou scored: %d\n", score);

    saveScore(playerName, score);

    int total = getPlayerScore(playerName);
    printf("Total Score Updated: %d\n", total);
}