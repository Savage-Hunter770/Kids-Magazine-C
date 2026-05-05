#ifndef FILE_SYSTEM_H // If FILE_SYSTEM_H is NOT defined yet (first time including this file)
#define FILE_SYSTEM_H // Define FILE_SYSTEM_H to mark this file as included

// ... Function declarations here ...
void saveScore(char name[], int score);
void showLeaderboard();
void resetLeaderboard();
int getPlayerScore(char playerName[]);

#endif // End of the condition started by #ifndef