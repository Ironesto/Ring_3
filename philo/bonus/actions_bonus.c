#include "philo_bonus.h"

void	the_final(t_philo *philo)
{
	if (philo->count >= philo->td)
	{
		philo->isdead = 1;
		printf("\n%sPHILO %d HA MUERTO%s\n", RED, philo->philo, RESET);
		exit(1);
	}
}

void	eating(t_philo *philo)
{
	time_t	temp;

	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s pensando\n",CYAN,
			philo->ttotal, GREEN, philo->philo, RESET);
	sem_wait(philo->sem_eat);
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s comiendo%s\n",CYAN,
			philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	philo->td = philo->count + philo->die;
	temp = philo->count + philo->eat;
	//printf("comiendo philo %d count es %ld temp es %ld\n", philo->philo, philo->count, temp);
	while (philo->count < temp)
	{
		//philo->count = ft_gettimephl(philo);
		//usleep(2000);
/* 		if (philo->count >= philo->td)
			puts("comiendo"); */
		//the_final(philo);
		//printf("hijo %d contador %ld y temp %ld\n",philo->philo, philo->count, temp);
		//usleep(1000);
	}
	sem_post(philo->sem_eat);
}

void	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s durmiendo%s\n",CYAN,
			philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{}
}
