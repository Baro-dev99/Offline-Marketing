#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void delay(int numberOfSeconds)
{
    // Converting time into milli_seconds
    int milliSeconds = 1000 * numberOfSeconds;

    // Stroing start time
    clock_t startTime = clock();      // clock_t is a suitable type for storing the processor time

    // looping till required time is not achieved
    while (clock() < startTime + milliSeconds);
}

void printLocalTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(timeinfo));
}
