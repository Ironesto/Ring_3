#include "philo_bonus.h"

void	the_final(t_philo *philo)
{
	if (philo->count >= philo->td)
	{
		printf("\n%sPHILO %d HA MUERTO%s\n", RED, philo->philo, RESET);
		exit(1);
	}
}

void	eating(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->eat;
	sem_wait(philo->sem_eat);
	printf("%s%ld tmls %sphilo %d%s comiendo%s\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(2000);
		if (philo->count >= philo->td)
			puts("comiendo");
		the_final(philo);
	}
	//philo->fork->forktb = 0;
	//philo->fork_l->forktb = 0;
	//pthread_mutex_unlock(&philo->fork->mutex_forktb);
	//pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
}

void	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	printf("%s%ld tmls %sphilo %d%s durmiendo%s\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(2000);
		if (philo->count >= philo->td)
			puts("durmiendo");
		the_final(philo);
	}
}

void	letsthink(t_philo *philo)
{
	philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
	printf("%s%ld tmls %sphilo %d%s pensando\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, RESET);
	while (philo->sem_eat == 0)
	{
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
	while (philo->sem_eat == 0)
	{
		philo->count = ft_gettimephl(philo);
		usleep(2000);
		if (philo->count >= philo->td)
			puts("pensando");
		the_final(philo);
	}
}
