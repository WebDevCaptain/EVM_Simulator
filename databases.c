// This file contains utility functions that write data to our File System

void _save_to_database(cand v) {
    /* Takes a Candidate, fetches his/her current votes, increase it by one and saves it back to
    the File System */
    int votes = 0;
    char filename[4];
    filename[0] = v.name[0];
    filename[1] = '-';
    filename[2] = v.party[0];
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &votes);
    fclose(fp);
    votes++;
    FILE *fp2 = fopen(filename, "w");
    fprintf(fp2, "%d \n", votes);
    fclose(fp2);
}


/* This function is very important for the current structure of our program. While calculating 
    the results, we run a configuration function called '_fetch_votes'. If we don't initialize
    files for storing candidates' votes, '_fetch_votes' will not able initialize our environment
    successfully and throw a very nasty error message. */
    
void initialize_files(cand v) {
    /* Takes a Candidate, and initializes a file (with a unique identifier) in the File System
     and puts 0 (which represents the number of votes) into it.  */

    int initial = 0;   // Initial number of Votes for a candidate
    char filename[4];

    /* Below three lines make a unique filename per candidate, which comprises of candidate's
     first name, a hyphen and his party symbol */
    filename[0] = v.name[0];
    filename[1] = '-';
    filename[2] = v.party[0];
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d \n", initial);
    fclose(fp);
}