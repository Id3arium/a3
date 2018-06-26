#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void* monitorCountdownTimer(void* runTime){
	printf("tmonitorCountdownTimer\n");
}

void* wallClock(void* runTime){
	int iterations = *(int*)runTime;
	int i = 0;
	for(i = 0; i < iterations ; i++){
		time_t rawtime;
		struct tm *time = localtime(&rawtime);
		printf("the current itme is: %d:%d:%d\n", time->tm_hour, time->tm_min, time->tm_sec);
		sleep(1);
	}
	printf("Alarm activated\n");
}

int main(int argc, char * argv[]){
	int runTime;
	pthread_t thread1, thread2;
	if (argc == 2) {
		runTime = atoi(argv[1]);
	} else {
		runTime = 25;
	}

	printf("satrting wallClock\n");
	pthread_create(&thread1, NULL, monitorCountdownTimer, &runTime); 
	printf("starting tmonitorCountdownTimer\n");
	pthread_create(&thread2, NULL, wallClock, &runTime); 	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("A friendly message.\n");
}

