#include "philo.h"

int	main(int argc, char **argv)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	long int a = time.tv_sec;
	long int i = time.tv_usec;
	while (1)
	{
		gettimeofday(&time, NULL);
		printf("tiempo es %ld segundos y %ld\n", time.tv_sec - a, (time.tv_usec));
	}
	return (0);
}

// 1 microsegundo / 1000 = 1 milisegundo
// 1 segundo * 1000 = 1 milisegundo
// usleep(unsigned long int) suspende la ejecucion d eun programa durante x microsegundos