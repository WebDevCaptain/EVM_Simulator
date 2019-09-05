// Contains the configuration functions for our EVM simulator

void _configure_evm() {
    /* Configures the EVM for the number of candidates, their names and party symbols and saves 
        all the information in a file called EVM.txt */
    int totalCandidates = 0;
    char name[60];
    char party[2];

    FILE *f = fopen("EVM.txt", "w");

    printf("How many candidates are contesting the Elections: ");
    scanf("%d", &totalCandidates);

    fprintf(f, "%d \n", totalCandidates);

    for (int i = 0; i < totalCandidates; i++) {
        printf("Name of the Candidate: ");
        scanf(" %s", name);
        printf("Election Symbol: ");
        scanf(" %s", party);
        fprintf(f, "%s", name);
        fprintf(f, " ");
        fprintf(f, "%s \n", party);
    }
    fclose(f);
}

void _configure_environment(int reset) {
    /* Loads data from EVM.txt into our program and changes the values of global variables
    like 'totalCandidates' and candidates array so that other functions can work seamlessly */
    int d = 0;
    int i = 0;
    cand c;

    FILE *f = fopen("EVM.txt", "r");
    fscanf(f, "%d", &d);
    
    totalCandidates = d;

    while (!feof(f)) {
        fscanf(f, "%s%s", c.name, c.party);
        candidates[i] = c;
        i++;
    }
    fclose(f);

    /* If reset flag is passed as 1, it will initialize the Files in the File System
     (for storing candidate's votes) with initial value of vote i.e 0 */
    if (reset == 1) {
        for (int j = 0; j < d; j++) {
            initialize_files(candidates[j]);
        }
    }
}

void _fetch_votes() {
    /* Fetches the votes from the file system and loads the data into our application's global
    variables. This will be used for calculating Results. */
    int votes = 0;
    for (int i = 0; i < totalCandidates; i++) {
        char filename[4];
        filename[0] = candidates[i].name[0];
        filename[1] = '-';
        filename[2] = candidates[i].party[0];
        FILE *fp = fopen(filename, "r");
        fscanf(fp, "%d", &votes);
        fclose(fp);
        candidates[i].votes = votes;
    }
}
