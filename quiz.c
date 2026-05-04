#include <stdio.h>
#include "quiz.h"
#include "file_system.h"

extern char playerName[50];

struct Question {
    char question[100];
    char options[4][50];
    int correctAnswer;
};

void startQuiz() {

    struct Question quiz[3] = {
        {"What is 2 + 2?",
         {"1", "2", "3", "4"},
         4},

        {"What color is the sky?",
         {"Blue", "Green", "Red", "Yellow"},
         1},

        {"Which is a fruit?",
         {"Car", "Apple", "Chair", "Table"},
         2}
    };

    int score = 0;
    int answer;

    printf("\n🧠 Quiz Time!\n");

    for(int i = 0; i < 3; i++) {
        printf("\n%s\n", quiz[i].question);

        for(int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, quiz[i].options[j]);
        }

        printf("Your answer: ");
        scanf("%d", &answer);

        if(answer == quiz[i].correctAnswer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong!\n");
        }
    }

    printf("\n=====================\n");
    printf("Final Score: %d/3\n", score);
    printf("=====================\n");
    saveScore(playerName, score);
}