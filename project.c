#include "project.h"
#include <stdlib.h>
#include <string.h>


struct Racer* add_driver(char *lastname, char *team, struct Racer *racerTimes, int numOfDrivers){
    // loop through all drivers and compare the drivers being added to make sure it is not added twice
    for(int i =0; i<numOfDrivers; i++){
        if(strcmp(racerTimes[i].name, lastname) == 0){
            printf("Racer already exists in the database.\n", lastname);
            return racerTimes;
        } 
    }

    //reallocate memory for racerTimes to the correct size 
    racerTimes = realloc(racerTimes, (numofDrivers+1)*sizeof(struct Racer));

    //dynamically allocate memory to both lastnames and team 
    racerTimes[numOfDrivers].name = malloc((strlen(lastname)+1)*sizeof(char));
    racerTimes[numOfDrivers].t= malloc((strlen(team)+1)*sizeof(char));

    //copy the string to the correct arrays
    strcpy(racerTimes[numOfDrivers].name, lastname);
    strcpy(racerTimes[numOfDrivers].t, team);

    // set all hours, minutes, seconds to 0 
    racerTimes[numOfDrivers].racer_times.s = 0; 
    racerTimes[numOfDrivers].racer_times.m = 0;
    racerTimes[numOfDrivers].racer_times.h = 0;

    numOfDrivers++;

    return racerTimes;
} 

int update_time(char *lastname, int hours, int minutes, int seconds, struct Racer *racerTimes, int numOfDrivers){
    //create a temporary variable that ensures this racer exists in the database
    int temp = 0;

    //loop through all drivers 
    for(int i=0; i<numOfDrivers; i++){
        if(strcmp(racerTimes[i].name, lastname) == 0){
            racerTimes[i].racer_times.h += hours;
            racerTimes[i].racer_times.m += minutes;
            racerTimes[i].racer_times.s += seconds;

            //we can give the temp a value now that we know the racer exists
            temp=1;
   
            //if minutes over 60, need to be added to hours
            if(racerTimes[i].racer_times.minutes>=60){
                racerTimes[i].racer_times.hours += racerTimes[i].racer_times.minutes/60;
                racerTimes[i].racer_times.minutes += racerTimes[i].racer_times.minutes%60;
            }
            //if seconds are over 60, needs to be added to minutes
            if(racerTimes[i].racer_times.seconds>=60){
                racerTimes[i].racer_times.minutes += racerTimes[i].racer_times.seconds/60;
                racerTimes[i].racer_times.seconds += racerTimes[i].racer_times.seconds%60;
            }
        }
    }
    if(temp == 0){
        printf("Error message driver has not been added to database");
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
        printf("%s %s %d:%d:%d\n", racerTimes[i].name, racerTimes[i].t, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
    }
    return 0;
}

int save_results(char *filename, struct Racer *racerTimes, int numOfDrivers){

    //open the 

    FILE *file_1 = fopen(filename, "a");
    if(!file_1){
        printf("File cant be opened");
        return -1;
    }
    for(int i=0; i<numOfDrivers; i++){
        fprintf(file_1, "%s %s %d %d %d", racerTimes[i].name, racerTimes[i].t, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
    }
    fclose(file_1);
    return 0;   
}

int load_results(char *filename, struct Racer *racerTimes, int numOfDrivers){
    FILE *file_1 = fopen(filename, "a");
    if(!file_1){
        printf("File cant be opened");
        return -1;
    }
    for(int i=0; i<numOfDrivers; i++){
        fscanf(file_1, "%s %s %d %d %d", racerTimes[i].name, racerTimes[i].t, &racerTimes[i].racer_times.hours, &racerTimes[i].racer_times.minutes, &racerTimes[i].racer_times.seconds);
    }
    fclose(file_1);
    return 0;
}

int exit_program(struct Racer *racerTimes, int numOfDrivers){
    for(int i=0; i<numOfDrivers; i++){
        free(racerTimes[i].name);
        free(racerTimes[i].t);
    }
    free(racerTimes);
    return 0;
}


int main(){
  
    int hours, minutes, seconds;
    int numOfDrivers = 0;
    int booll= 1;
  
    char rep1[1000];
    char rep2[1000];
    struct Racer *racerTimes = NULL;
    
    
    char letter;
    printf("Enter a letter: \n");

    while(booll){

        scanf("%c", &letter);

        if(letter == 'A'){
            scanf("%s %s", rep1, rep2);
            numOfDrivers++;
            racerTimes = add_driver(rep1, rep2, racerTimes, numOfDrivers);
            break;
        }                
        else if(letter == 'U'){
            scanf("%s %d %d %d", rep1, &hours, &minutes, &seconds);
            update_time(rep1, hours, minutes, seconds, racerTimes, numOfDrivers);
            break;
        }       
        else if(letter == 'L'){
            print_results(racerTimes, numOfDrivers);
            break;
        }    
        else if(letter == 'W'){
            scanf("%s", rep1);
            save_results(rep1, racerTimes, numOfDrivers);
            break;
        }    
        else if(letter == 'O'){
            scanf("%s", rep2);
            load_results(rep2, racerTimes, numOfDrivers);
            break;
        }    
        else if(letter == 'Q'){
            booll = 0;
            exit_program(racerTimes, numOfDrivers);
            break;
        }
        else{
            printf("You did not enter a correct input");
            break;
        }
    }
} 
