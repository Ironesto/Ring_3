#include "philo.h"

static int	ft_putnbr_atoi(const char *str, int i)
{
	long	num;

	num = 0;
	while (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		num += (str[i] - '0');
		num *= 10;
		i++;
	}
	num += (str[i] - '0');
	return (num);
}

int	ft_atoi(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		return (ft_putnbr_atoi(nptr, i + 1));
	if (nptr[i] == '-' && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		return (ft_putnbr_atoi(nptr, i + 1) * -1);
	if (nptr[i] >= '0' && nptr[i] <= '9')
		return (ft_putnbr_atoi(nptr, i));
	return (0);
}

time_t	ft_gettime(struct timeval time, time_t sec)
{
	time_t	t;
	
	gettimeofday(&time, NULL);
	t = (time.tv_sec - sec) * 1000 + (time.tv_usec / 1000);
	return (t);
}

int	main(int argc, char **argv)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	while (1)
	{
		//pthread_create();
		//printf("filosofos son: %d, die:%d eat: %d, sleep: %d\n", ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
		printf("%ld mls\n", ft_gettime(time, time.tv_sec));
		usleep(1 * 1000000);
	}
	return (0);
}

// 1 microsegundo / 1000 = 1 milisegundo
// 1 segundo * 1000 = 1 milisegundo
// usleep(unsigned long int) suspende la ejecucion d eun programa durante x microsegundos