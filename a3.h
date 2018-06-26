#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int runTime;
pthread_t thread1, thread2;
time_t rawtime;
int hours, minutes, seconds;

void* wallClock(void* runTime);
void* monitorCountdownTimer(void* runTime);
