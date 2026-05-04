#include <stdio.h>
#include <stdlib.h>
#include "story.h"
#include "file_system.h"
#include "games.h"

extern char playerName[50];

// ---------------- FUNCTION PROTOTYPES ----------------
void toddlerStory(int *health);
void kidStory(int *health);
void checkHealth(int health);

// ---------------- MAIN STORY FUNCTION ----------------
void startStory() {
    int age;
    int playerHealth = 30;

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age < 3 || age > 11) {
        printf("\nSorry %s, this magazine is only for ages 3 to 11.\n", playerName);
        return;
    }

    printf("\n--- Welcome %s to the Magic Magazine Adventure! ---\n", playerName);
    printf("Starting Health: %d\n", playerHealth);

    if (age <= 6) {
        toddlerStory(&playerHealth);
    } else {
        kidStory(&playerHealth);
    }

    printf("\n%s, your journey is complete. Final Health: %d\n", playerName, playerHealth);

    // 🎯 SCORING SYSTEM (your table)
    int score;

    if (playerHealth <= 30) {
        score = 1;
    } else if (playerHealth <= 70) {
        score = 3;
    } else {
        score = 5;
    }

    printf("You earned %d points from this story!\n", score);

    // Save to leaderboard
    saveScore(playerName, score);
    printf("Score saved to leaderboard!\n");

    // Rank system (unchanged)
    if (playerHealth > 100) {
        printf("Rank: Legendary Hero!\n");
    } else if (playerHealth > 50) {
        printf("Rank: Brave Explorer!\n");
    } else if (playerHealth > 0) {
        printf("Rank: Survivor!\n");
    }
}

// ---------------- INPUT VALIDATION ----------------


// ---------------- HEALTH CHECK ----------------
void checkHealth(int health) {
    if (health <= 0) {
        printf("\n💀 Your health dropped to 0...\n");
        printf("GAME OVER!\n");
        exit(0);
    }
}

// ---------------- TODDLER STORY (LONG VERSION) ----------------
void toddlerStory(int *health) {
    int choice;

    printf("\n[Stage 1: The Sunny Meadow]\n");
    printf("You wake up in a bright meadow full of colorful flowers.\n");
    printf("Butterflies fly around you, and the sun feels warm.\n");
    printf("Suddenly, a glowing Magic Tree waves its branches at you.\n");
    printf("It looks friendly and wants to play.\n");
    printf("1. Hug the tree\n2. Shake the tree\n");

    choice = getValidChoice(1, 2);

    if (choice == 1) {
        printf("The tree giggles happily and gives you a golden fruit! +20 Health\n");
        *health += 20;
    } else {
        printf("A beehive falls and bees chase you! You run away scared! -15 Health\n");
        *health -= 15;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nThe tree whispers softly: 'Follow the river... it will take you home.'\n");

    printf("\n[Stage 2: The Talking River]\n");
    printf("You arrive at a sparkling river with shining blue water.\n");
    printf("The water is moving fast, and it looks hard to cross.\n");
    printf("A glowing fish jumps out and says: 'I know a safe way!'\n");
    printf("1. Listen to the fish\n2. Ignore it and cross alone\n");

    choice = getValidChoice(1, 2);

    if (choice == 1) {
        printf("The fish shows you safe stepping stones across the river! +15 Health\n");
        *health += 15;
    } else {
        printf("You slip on wet rocks and fall into the cold water! -15 Health\n");
        *health -= 15;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nAfter crossing the river, you see a dark cave ahead.\n");
    printf("It is the only way forward...\n");

    printf("\n[Stage 3: The Sleepy Giant]\n");
    printf("A giant is sleeping in front of the cave entrance.\n");
    printf("He is huge and blocks your path home.\n");
    printf("1. Sing a lullaby\n2. Try to run past him\n");

    choice = getValidChoice(1, 2);

    if (choice == 1) {
        printf("Your gentle song makes the giant smile in his sleep.\n");
        printf("He rolls over and clears the path! +10 Health\n");
        *health += 10;
    } else {
        printf("You trip while running and wake the giant!\n");
        printf("He stomps loudly and scares you! -25 Health\n");
        *health -= 25;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nYou quietly walk through the cave and finally find your way home.\n");
    printf("You feel proud of your adventure!\n");
}

// ---------------- KID STORY (LONG VERSION) ----------------
void kidStory(int *health) {
    int choice;

    printf("\n[Level 1: The Dark Forest]\n");
    printf("You step into a dark forest where shadows move between trees.\n");
    printf("The wind whispers your name, and the air feels cold.\n");
    printf("You notice an old map lying under a rock.\n");
    printf("1. Follow the map\n2. Trust your instincts\n");

    choice = getValidChoice(1, 2);

    if (choice == 1) {
        printf("The map guides you safely through the forest.\n");
        printf("You find a hidden potion glowing under a tree! +25 Health\n");
        *health += 25;
    } else {
        printf("You wander into thick thorns that scratch your skin badly! -20 Health\n");
        *health -= 20;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nAt the end of the forest, a ruined castle appears in the distance.\n");

    printf("\n[Level 2: The Haunted Castle]\n");
    printf("The castle is surrounded by fog and complete silence.\n");
    printf("You hear faint whispers coming from inside.\n");
    printf("The gate is locked, but a broken window is nearby.\n");
    printf("1. Sneak through the window\n2. Break the gate open\n");

    choice = getValidChoice(1, 2);

    if (choice == 1) {
        printf("You carefully climb through the window and avoid hidden traps.\n");
        printf("Inside, you discover a secret treasure room filled with magic! +30 Health\n");
        *health += 30;
    } else {
        printf("The loud crash alerts ghost guards!\n");
        printf("They surround you and attack from all sides! -30 Health\n");
        *health -= 30;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nAs you go deeper, the air becomes colder...\n");
    printf("A powerful presence awakens.\n");

    printf("\n[Level 3: Final Boss - The Shadow Knight]\n");
    printf("A dark knight appears, surrounded by black energy.\n");
    printf("'You shall not leave this place alive,' he says.\n");
    printf("1. Fight with your sword\n2. Use a magic spell\n");

    choice = getValidChoice(1, 2);

    if (choice == 2) {
        printf("Your magic spell shines brightly and breaks the darkness!\n");
        printf("The knight disappears into shadows! +40 Health\n");
        *health += 40;
    } else {
        printf("The knight is too powerful in combat!\n");
        printf("He strikes you down with heavy force! -50 Health\n");
        *health -= 50;
    }

    printf("Health: %d\n", *health);
    checkHealth(*health);

    printf("\nThe castle begins to collapse as light returns.\n");
    printf("You escape just in time... victorious!\n");
}