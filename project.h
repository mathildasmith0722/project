#ifndef project_h
#define project_h

#include <stdio.h>

struct Time{
    int hours;
    int minutes;
    int seconds;
}

struct Racer{
    char *lastname;
    char *team;
    struct Time racer_time;
}


struct Racer* add_driver(char *lastname, char *team, struct Racer *racerTimes);
int update_time(char *lastname, int hours, int minutes, int seconds, struct Driver *racerTimes, int numOfDrivers);
int comparison(const void *racer_time1, const void racer_time2);
int print_results(struct Racer *racerTimes, int noDrivers);
int save_results(char *filename, struct Racer *racerTimes, int numOfDrivers);
int load_results(char *filename, struct Racer *racerTimes, int numOfDrivers);
int exit_program();

#endif

