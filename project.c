#include "project.h"
#include <stdlib.h>
#include <string.h>


struct Racer* add_driver(char *lastname, char *team, struct Racer *racerTimes, int numOfDrivers){
    racerTimes = realloc(racerTimes,  numOfDrivers*sizeof(struct Racer));
    racerTimes[numOfDrivers - 1].lastname = malloc((strlen(lastname)+1)*sizeof(char));
    racerTimes[numOfDrivers - 1].team = malloc((strlen(team)+1)*sizeof(char));

    strcopy(racerTimes[numOfDrivers-1].lastname, lastname);
    strcopy(racerTimes[numOfDrivers-1].team, team);

    racerTimes[numOfDrivers - 1].racer_times.seconds = 0;
    racerTimes[numOfDrivers - 1].racer_times.minutes = 0;
    racerTimes[numOfDrivers - 1].racer_times.hours = 0;

    return racerTimes;
}

int update_time(char *lastname, int hours, int minutes, int seconds, struct Racer *racerTimes, int numOfDrivers){
    int num = 0;
    for(int i=0; i<numOfDrivers; i++){
        if(strcmp(racerTimes[i].lastname, lastname) == 0){
            racerTimes[i].racer_times.hours += hours;
            racerTimes[i].racer_times.minutes += minutes;
            num=1;
            racerTimes[i].racer_times.seconds += seconds;

            if(racerTimes[i].racer_times.minutes>=60){
                racerTimes[i].racer_times.hours += racerTimes[i].racer_times.minutes/60;
                racerTimes[i].racer_times.minutes += racerTimes[i].racer_times.minutes%60;
            }
            if(racerTimes[i].racer_times.seconds>=60){
                racerTimes[i].racer_times.minutes += racerTimes[i].racer_times.seconds/60;
                racerTimes[i].racer_times.seconds += racerTimes[i].racer_times.seconds%60;
            }
        }
    }
    if(num == 0){
        printf("Error message driver has not been added to database");
    }
    return 0;
    
}

int comparison(const void *racer_time1, const void *racer_time2){

    const struct Racer *time_11 = racer_time1;
    const struct Racer *time_22 = racer_time2;
    int time_1 = (time_11 -> racer_times.hours*60*60) + (time_11 -> racer_times.minutes*60) + (time_11-> racer_times.seconds);
    int time_2 = (time_22 -> racer_times.hours*60*60) + (time_22 -> racer_times.minutes*60) + (time_22 -> racer_times.seconds);

    return abs(time_1 - time_2);
}

int print_results(struct Racer *racerTimes, int numOfDrivers){
    qsort(racerTimes, numOfDrivers, sizeof(struct Racer), comparison);
    for(int i=0; i< numOfDrivers; i++){
        printf("%s %s %d:%d:%d\n", racerTimes[i].lastname, racerTimes[i].team, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
    }
    return 0;
}

int save_results(char *filename, struct Racer *racerTimes, int numOfDrivers){
    FILE *file_1 = fopen(filename, "a");
    if(!file_1){
        printf("File cant be opened");
        return -1;
    }
    for(int i=0; i<numOfDrivers; i++){
        fprintf(file_1, "%s %s %d %d %d", racerTimes[i].lastname, racerTimes[i].team, racerTimes[i].racer_times.hours, racerTimes[i].racer_times.minutes, racerTimes[i].racer_times.seconds);
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
        fscanf(file_1, "%s %s %d %d %d", racerTimes[i].lastname, racerTimes[i].team, &racerTimes[i].racer_times.hours, &racerTimes[i].racer_times.minutes, &racerTimes[i].racer_times.seconds);
    }
    fclose(file_1);
    return 0;
}

int exit_program(struct Racer *racerTimes, int numOfDrivers){
    for(int i=0; i<numOfDrivers; i++){
        free(racerTimes[i].lastname);
        free(racerTimes[i].team);
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

        switch (letter) {
            case 'A':
                scanf("%s %s", rep1, rep2);
                numOfDrivers++;
                racerTimes = add_driver(rep1, rep2, racerTimes, numOfDrivers);
                break;
                
            case 'U':
                scanf("%s %d %d %d", rep1, &hours, &minutes, &seconds);
                update_time(rep1, hours, minutes, seconds, racerTimes, numOfDrivers);
                break;
                
            case 'L':
                print_results(racerTimes, numOfDrivers);
                break;
                
            case  'W':
                scanf("%s", rep1);
                save_results(rep1, racerTimes, numOfDrivers);
                break;
                
            case 'O':
                scanf("%s", rep2);
                load_results(rep2, racerTimes, numOfDrivers);
                break;
                
            case 'Q':
                booll = 0;
                exit_program(racerTimes, numOfDrivers);
                break;
                
            default:
                printf("You did not enter a correct input");
                break;

        }
    }   
}


