


struct Racer* add_driver(char *lastname, char *team, struct Racer *racerTimes, int numOfDrivers){

}

int update_time(char *lastname, int hours, int minutes, int seconds, struct Driver *racerTimes, int numOfDrivers){
    int num = 0;
    for(int i=0; i<numOfDrivers; i++){
        if(strcmp(racerTimes[i].lastname, lastname) == 0){
            racerTimes[i].racer_times.hours += hours;
            racerTimes[i].racer_times.minutes += minutes;
            racerTimes[i].racer_times.seconds += seconds;

            num = 1;
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

int comparison(const void *racer_time1, const void racer_time2){
    const struct Racer *order1 = racer_time1;
    const struct Racer *order2 = racer_time2;
    int time1 = (order1 -> racer_times.hours) + (order1 -> racer_times.minutes) (order1 -> racer_times.seconds)
    int time2 = (order2 -> racer_times.hours) + (order2 -> racer_times.minutes) (order2 -> racer_times.seconds)

    return (time1 - time2);
}

int print_results(struct Racer *racerTimes, int noDrivers){
    qsort(racerTimes, noDrivers, sizeof(struct Racer), comparison);
    for(int i=0; i< noDrivers; i++){
        printf("%s %s %d:%d:%d\n", racerTimes[i].last_name, racerTimes[i].team,
        racerTimes[i].racer_time.hours, racerTimes[i].racer_time.minutes,
        racerTimes[i].racer_time.seconds);
    }
    return 0;
}

int save_results(char *filename, struct Racer *racerTimes, int numOfDrivers){
    FILE *file_1 = fopen(filename, "a")
    if(!file_1){
        printf("File cant be opened");
        return -1;
    }
    for(int i=0; i<numOfDrivers; i++){
        fprintf(file_1, "%s %s %s %d %d", racerTimes[i].lastname, racerTimes[i].team, &racerTimes[i].racer_times.hours, &racerTimes[i].racer_times.minutes, &racerTimes[i].racer_times.seconds);
    }
    fclose(file_1);
    return 0;   
}

int load_results(char *filename, struct Racer *racerTimes, int numOfDrivers){
    FILE *file_1 = fopen(filename, "a")
    if(!file_1){
        printf("File cant be opened");
        return -1;
    }
    for(int i=0; i<numOfDrivers; i++){
        fscan(file_1, "%s %s %s %d %d", racerTimes[i].lastname, racerTimes[i].team, &racerTimes[i].racer_times.hours, &racerTimes[i].racer_times.minutes, &racerTimes[i].racer_times.seconds);
    }
    fclose(file_1);
    return 0;
}

int main(){
  
  int hours, minutes, seconds;
  int numOfDrivers = 0;
  int num = 1;
  
  char rep1[1000];
  char rep2[1000];
  struct Racer *racerTimes = NULL;
    
    
    char firstLetter;
    printf("Please enter an input: \n");
    while(FLAG)
  switch (firstLetter) {
    case 'A':
      scanf("%s %s", buffer1, buffer2);
        numOfDrivers++;
          driverTimes = addDriver(buffer1  , buffer2, driverTimes, numberOfElements);
          break;
                
            case 'U':
                scanf("%s %d %d %d", buffer1, &hours, &minutes, &seconds);
                updateTotalTime(buffer1, hours, minutes, seconds, driverTimes, numberOfElements);
                break;
                
            case 'L':
                printResults(driverTimes, numberOfElements);
                break;
                
            case  'W':
                scanf("%s", buffer1);
                saveResults(buffer1, driverTimes, numberOfElements);
                break;
                
            case 'O':
                scanf("%s", buffer2);
                loadResults(buffer2, driverTimes, numberOfElements);
                break;
                
            case 'Q':
                FLAG = 0;
                break;
                
            default:
                break;
        }
}

