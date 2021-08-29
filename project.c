#include "project.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


struct Racer* add_driver(char *lastname, char *team, struct Racer *racerTimes, int numOfDrivers){

    
    // loop through all drivers and compare the drivers being added to make sure it is not added twice
    int i = 0;
    while(i<numOfDrivers){
        if(strcmp(racerTimes[i].lastname, lastname) == 0){
            printf("Driver \"%s\" is already in the database.\n", lastname);
            return NULL;
        }
        ++i;
    }

    //reallocate memory for racerTimes to the correct size
 
    racerTimes = realloc(racerTimes, (numOfDrivers+1)*sizeof(struct Racer));

    //dynamically allocate memory to both lastnames and team

    racerTimes[numOfDrivers].lastname = calloc( (strlen(lastname)+1), sizeof(char) );
    racerTimes[numOfDrivers].team= calloc((strlen(team)+1), sizeof(char));

    //copy the string to the correct arrays

    strcpy(racerTimes[numOfDrivers].lastname, lastname);
    strcpy(racerTimes[numOfDrivers].team, team);


    // set all hours, minutes, seconds to 0

    racerTimes[numOfDrivers].racer_times.seconds = 0; 
    racerTimes[numOfDrivers].racer_times.minutes = 0;
    racerTimes[numOfDrivers].racer_times.hours = 0;

    printf("SUCCESS\n");
    return racerTimes;
} 

int update_time(char *lastname, int hours, int minutes, int seconds, struct Racer *racerTimes, int numOfDrivers){
    //create a temporary variable that ensures this racer exists in the database

    int temp = -1;

    //check that all seconds, minutes, hours are valid    

    if((hours < 0)){
        printf("Hour cannot be negative.\n");
        return 0; 
    }
    else if((minutes >= 60) || (minutes< 0)){
        printf("Minute cannot be negative or greater than 59.\n");
        return 0;
    }

    else if((seconds >= 60) || (seconds< 0)){
        printf("Second cannot be negative or greater than 59.\n");
        return 0; 
    }

    //loop through all drivers

    else{
        for(int i=0; i<numOfDrivers; i++){
            if(strcmp(racerTimes[i].lastname, lastname) == 0){
                racerTimes[i].racer_times.hours += hours;
                racerTimes[i].racer_times.minutes += minutes;

                //we can give the temp a value now that we know the racer exists

                racerTimes[i].racer_times.seconds += seconds;
                temp =1;

                //if seconds are over 60, needs to be added to minutes

                if(racerTimes[i].racer_times.seconds>=60){
                    racerTimes[i].racer_times.minutes += racerTimes[i].racer_times.seconds/60;
                    racerTimes[i].racer_times.seconds = racerTimes[i].racer_times.seconds%60;
                }

                //if minutes over 60, need to be added to hours

                if(racerTimes[i].racer_times.minutes>=60){
                    racerTimes[i].racer_times.hours += racerTimes[i].racer_times.minutes/60;
                    racerTimes[i].racer_times.minutes = racerTimes[i].racer_times.minutes%60;
                }
                
                printf("SUCCESS\n");  
            }
        }
    }
    //print error message if necessary

    if(temp == -1){
        printf("Driver \"%s\" is not in the database.\n", lastname);
    }
    
    return 0;
    
}

int subtract(const void *racer_time1, const void *racer_time2){

    const struct Racer *time_11 = racer_time1;
    const struct Racer *time_22 = racer_time2;

    //calculate the time in seconds for simple subtraction

    int time_1 = (time_11 -> racer_times.hours*60*60) + (time_11 -> racer_times.minutes*60) + (time_11-> racer_times.seconds);
    int time_2 = (time_22 -> racer_times.hours*60*60) + (time_22 -> racer_times.minutes*60) + (time_22 -> racer_times.seconds);

    return (time_1 - time_2);
} 

int print_results(struct Racer *racerTimes, int numOfDrivers){

    //sort the drivers based on their times
    qsort(racerTimes, numOfDrivers, sizeof(struct Racer), subtract);

    //loop through all drivers and print the name, team, and time of the driver

    for(int i=0; i< numOfDrivers; i++){
        printf("%s %s %d %d %d\n", racerTimes[i].lastname, racerTimes[i].team, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
    }
    return 0;
}

int save_results(char *filename, struct Racer *racerTimes, int numOfDrivers){

    //open the file, ensure it can be opened

    FILE *file_1 = fopen(filename, "w");
    if(!file_1){
        printf("File open error\n");
        return -1;
    }

    qsort(racerTimes, numOfDrivers, sizeof(struct Racer), subtract);
    //run through all the drivers and add their details to the file

    for(int i=0; i<numOfDrivers; i++){
        fprintf(file_1, "%s %s %d %d %d", racerTimes[i].lastname, racerTimes[i].team, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
    }
    //close the file

    fclose(file_1);
    return 0;   
}

int load_results(char *filename, struct Racer *racerTimes, int numOfDrivers){

    //open the file, ensure it can be opened

    FILE *file_1 = fopen(filename, "r");
    if(!file_1){
        printf("Cannot open file %s for reading.\n", filename);
        return -1;
    }
    //run through all the drivers and scan their results

    for(int i=0; i<numOfDrivers; i++){
        fscanf(file_1, "%s %s %d %d %d", racerTimes[i].lastname, racerTimes[i].team, &racerTimes[i].racer_times.hours, &racerTimes[i].racer_times.minutes, &racerTimes[i].racer_times.seconds);
    }
    //close the file

    fclose(file_1);
    printf("SUCCESS\n");
    return 0;
}

int exit_program(struct Racer *racerTimes, int numOfDrivers){
    //loop through drivers and free the memory for the racer and team

    for(int i=0; i<numOfDrivers; i++){
        free(racerTimes[i].lastname);
        free(racerTimes[i].team);
    }
    free(racerTimes);
    printf("SUCCESS\n");
    return 0;
}


int main(void){
    //initialize all variables needed

    int hours, minutes, seconds;
    int numOfDrivers = 0;
    int booll= 1;

    //create two buffers and the racer times are empty

    char rep1[1000] = {0};
    char rep2[1000] = {0};
    char buffer[1000] = {0};
    struct Racer *racerTimes = NULL;
    
    int x;
    
    
    char letter[100] = {0};
    while(booll){
        fgets(buffer, 1000, stdin);
        sscanf(buffer, "%s", letter);
        switch(letter[0]){
            case 'A':
                x = sscanf(buffer, "%s %s %s", letter, rep1, rep2);
                if(x<3){
                    printf("A should be followed by exactly 2 arguments.\n");
                }
                else{
                    struct Racer *racerTimes2 = add_driver(rep1, rep2, racerTimes, numOfDrivers);
                    if (racerTimes2 != NULL){
                        numOfDrivers++;
                        racerTimes = racerTimes2;
                    }  
                }
                break;
                           
            case 'U':
                x = sscanf(buffer, "%s %s %d %d %d", letter, rep1, &hours, &minutes, &seconds);
                if(x<5){
                    printf("U should be followed by exactly 4 arguments.\n");
                }
                else{
                    update_time(rep1, hours, minutes, seconds, racerTimes, numOfDrivers);
                }
                break;  
                   
            case 'L':
                print_results(racerTimes, numOfDrivers);
                printf("SUCCESS\n");
                break;
                
            case 'W':
                sscanf(buffer, "%s %s", letter, rep1);
                save_results(rep1, racerTimes, numOfDrivers);
                printf("SUCCESS\n");
                break;
                
            case 'O':
                sscanf(buffer, "%s %s", letter, rep2);
                load_results(rep2, racerTimes, numOfDrivers);
                break;
                
            case 'Q':
                booll = 0;
                exit_program(racerTimes, numOfDrivers);
                break;
            
            default:
                printf("Invalid command %s\n", letter);
        }   
    }
    return 0;
}
