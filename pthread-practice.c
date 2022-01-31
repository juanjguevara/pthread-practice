#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *print_letters(void *letters);

main()
{
	pthread_t thread1, thread2;
	char *letterA = "AAAAAAAAA";
	char *letterB = "BBBBBBBBB";

	pthread_setconcurrency(2);

	pthread_create(&thread1, NULL, print_letters, (void*) letterA);
	pthread_create(&thread2, NULL, print_letters, (void*) letterB);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	exit(0);
}

void *print_letters(void *letters)
{
	int i, j;

	for(i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		for(j = 0; j < 5; j++) {
			printf("%02i: %s\n", (i + 1), (char*) letters);
			sleep(1);
		}
		printf("\n");
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}
