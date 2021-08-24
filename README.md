Rally

Implement a results system for a rally race that consists of several special stages. For each driver, the last name is stored, along with his team. In addition, 
the system maintains the overall time for each driver. Time consists of hours, minutes, and seconds. You can decide how the time is stored in memory, but it should 
be possible to store an arbitrarily large number of drivers. You can assume that the last name identifies the driver. For strings, at least 20 characters should be 
supported, but but you can decide how to handle longer strings.

The program has the following functions:

A lastname team : Add driver

Adds driver named ”lastname” to the database, who is representing ”team”. Initially, the total time will be 0 seconds. For example: A Kankkunen Renault (1 p)

U lastname hours minutes seconds : Update total time

Adds the given time to drivers total time, for example after a completed special stage. For example: U Kankkunen 0 52 16 will add 52 minutes and 16 seconds to the 
total time of driver Kankkunen. If the given driver was not yet added to the database, an error message should be printed. (1 p)

L: Print results

Prints the current results of the race, i.e., all drivers along with their teams and total times, each on a separate line. The drivers should be printed fastest 
first, i.e., the driver with smallest total time will be printed first. This command is worth of two points such that a correct output of all drivers (and other 
data) will provide one point, even if the order is wrong. If the order is correct, you will get another point. Remember that an hour has at most 60 minutes, and a 
minute has at most 60 seconds (max. 2 p)

W filename: Save results

Writes the current database to file with given filename. (1 p)

O filename: Load results

Loads the database from file, and replaces the existing results. (1 p)

Q : Exit program

Exits program and releases all allocated memory. This operation must be implemented so that you can find all possible memory leaks.
