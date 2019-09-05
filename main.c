#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* The 'Candidate' aka 'cand' type, representing the candidates in the election. It is the most
fundamental data-structure used in our EVM simulator program */
struct Candidate {
    char name[60];
    char party[2];
    int votes;
};
typedef struct Candidate cand;


// Global variables required inside all functions
int totalCandidates = 0;

/* Following line assumes that there are at most 10 people contesting the elections.
  We can increase the value to incorporate more candidates, or decrease it to save space,
  on our Stack memory. It's very difficult to move this global variable from Stack 
  to Heap, while preserving the current struture of the Program and without using bad
  practices. */
cand candidates[10];


// Importing our utility functions
#include "databases.c"
#include "config.c"
#include "results.c"

void menu();
void verify(cand c);


int main() {
    // Handles the flow of the EVM simulator
    int choice = 0;
    printf("Press 1 to configure EVM \nPress 2 to record votes \
     \nPress 3 to display results \nPress 4 to display winner: ");

    scanf("%d", &choice);

    if (choice == 1) {
        _configure_evm();
    } 
    else if (choice == 2) {
        // Contains logic to record votes
        int cap = 0;
        printf("How many votes do you want to record: ");
        scanf("%d", &cap);

        _configure_environment(1);

        for (int i = 0; i < cap; i++) {
            menu();
            /* Puts the main thread to sleep for one second. 
                It's there for making the UI feel more natural to the voters */
            sleep(1);

            /* Clears the terminal. It's an alternative to the clrscr() which is no longer
               available in the latest GNU compilers for C */
            system("clear");
        }
    } 
    else if (choice == 3) {
        // Configures the environment and display's the Results.
        _configure_environment(0);
        _fetch_votes();
        _display_results();
    } 
    else if (choice == 4) {
        // Configures the environment and display the winner.
        _configure_environment(0);
        _fetch_votes();
        _display_winner();
    } 
    else {
        printf("Invalid Choice \n");
    }
    return 0;
}

void menu() {
    // Menu for the main voting interface
    int choice;
    cand c;

    /* Prints all the candidate details to the terminal so that voters can choose their candidate
     by pressing the number corresponding to their favourite candidate. */
    for (int i = 0; i < totalCandidates; i++) {
        printf("%d ===> %s => %s \n", i + 1, candidates[i].name, candidates[i].party);
    }
    printf("Press the number next to the candidate of your choice: ");
    scanf("%d", &choice);

    // Checks if the choice is out of Bounds.
    if (choice <= 0 || choice > totalCandidates) {
        printf("Invalid Choice. Please Try Again. \n");
        scanf("%d", &choice);
    }

    if (choice > 0 && choice <= totalCandidates) {
        c = candidates[choice - 1];
    } else {
        printf("Vote not recorded. Please contact the Election Officer. \n");
        return;
    }

    // Confirmation popup.
    verify(c);
}

void verify(cand c) {
    // Gives a last chance to the voter to confirm his/her vote
    int choice;
    printf("You voted for => Candidate %s '%s' party \n", c.name, c.party);
    printf("Press 1 to confirm and Press 2 to cancel: ");
    scanf("%d", &choice);
    if (choice == 1) {
        _save_to_database(c); // Saves the vote for the candidate in the File system.
        printf("Done ! \n");
    } else {
        printf("Vote not recorded !!! \n");
    }
}
