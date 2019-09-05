/* This file contains all the logic to display the results and winner, calculated from the voting
 data available in the File System */


void _display_winner() {
    /* Displays the winner of the elections. It relies on global variables which are configured
       by the configuration functions in the 'config.c'. It also contains some very custom logic
       to determine if there is a draw and displays appropriate message in the terminal */
    cand winner = candidates[0];
    int possibleWinner = 1;
    cand* winnerList = (cand*) malloc(totalCandidates * sizeof(cand));
    for (int i = 1; i < totalCandidates; i++) {
        if (candidates[i].votes > winner.votes) {
            winner = candidates[i];
            possibleWinner = 1;
            winnerList[0] = candidates[i];
        } else if (candidates[i].votes == winner.votes) {
            winnerList[possibleWinner] = candidates[i];
            possibleWinner++;
        }
    }
    
    if (possibleWinner == 1) {
        printf("\n Winner is => %s \n", winner.name);
        printf("%s got %d votes\n", winner.name, winner.votes);
    } else {
        printf("\n There is a Draw between below %d candidates \n", possibleWinner);
        printf("Candidate: %s of %s party ==> %d votes \n", winner.name, winner.party, winner.votes);
        for (int j = 1; j < possibleWinner; j++) {
            cand politician = winnerList[j];
            printf("Candidate: %s of %s party ==> %d votes \n", 
                politician.name, politician.party, politician.votes);
        }
    }
    return;
}

void _display_results() {
    /* Displays the result, that comprises of candidate name, party symbol and total votes 
      received. It relies on global variables like 'totalCandidates' and 'candidates' array 
     that are configured by the functions in the 'config.c' file */
    cand c;
    printf("Candidate-Name Party-Symbol Total-Votes\n");
    for (int i = 0; i < totalCandidates; i++) {
        c = candidates[i];
        printf("%s \t %s \t %d\n", c.name, c.party, c.votes);
    }
}
