#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

time_t rawtime;
int hours, minutes, seconds;

void* monitorCountdownTimer(void* runTime){
	int iterations = *(int*)runTime;
	hours = iterations / 3600;
	minutes = (iterations / 60) % 60;
	seconds = iterations % 60;
	int i;
	for(i = 0; i <= iterations ; i++){
		printf("Countdown: %d:%d:%d\n", hours, minutes, seconds);
		if (--seconds == -1){ //decrease the seconds and set them back to 59 if a minute is over
			seconds = 59;
			if (--minutes == -1){ //decrease the minutes and set them back to 59 if an hour is over
				minutes = 59;
				hours--; //decrease the ours
			}
		}
		sleep(1);
	}
	printf("You're late! You're late! For a very important date!\n");
	//kill sibling
	//commit sudoku
}

void* wallClock(void* runTime){
	int iterations = *(int*)runTime;
	int i;
	//print the time every second the for as long as the user specified
	for(i = 0; i <= iterations; i++){
		time(&rawtime); //get the current time 
		struct tm *time = localtime(&rawtime); //store it in a struct to get only hrs,min,sec
		printf("The current time is: %d:%d:%d \n", time->tm_hour, time->tm_min, time->tm_sec);
		sleep(1);
	}
}

int main(int argc, char * argv[]){
	int runTime;
	pthread_t thread1, thread2;
	if (argc == 2) {
		runTime = atoi(argv[1]);
	} else {
		runTime = 25;
	}
	pthread_create(&thread1, NULL, monitorCountdownTimer, &runTime); 
	pthread_create(&thread2, NULL, wallClock, &runTime); 	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("A friendly message.\n");
}
