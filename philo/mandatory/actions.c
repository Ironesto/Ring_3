#include "philo.h"

void	letseat(t_philo *philo)
{
	time_t	temp;

	//philo->tnow = ft_gettimephl(philo);
	temp = philo->tnow + philo->teat;
	pthread_mutex_lock(&philo->fork->mutex_forktb);
	pthread_mutex_lock(&philo->fork_l->mutex_forktb);
	philo->fork->forktb = 1;
	philo->fork_l->forktb = 1;
	philo->final = philo->tnow + philo->tdie;
	printf("%ld philo %d esta comiendo\n", philo->ms[0], philo->philo);
	while (philo->tnow < temp)
	{
		philo->tnow = ft_gettimephl(philo);
		if (philo->tnow >= philo->final)
		{
			printf("%d comiendo tnow %ld y final %ld",philo->philo, philo->tnow, philo->final);
			printf("\n\nPHILO %d HA MUERTO COMIENDO\n\n", philo->philo);
			exit(1);
		}
	}
	philo->fork->forktb = 0;
	philo->fork_l->forktb = 0;
	pthread_mutex_unlock(&philo->fork->mutex_forktb);
	pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
}

void	letsleep(t_philo *philo)
{
	time_t	temp;

	//philo->tnow = ft_gettimephl(philo);
	temp = philo->tnow + philo->tslp;
	printf("%ld philo %d esta durmiendo\n", philo->ms[0], philo->philo);
	while (philo->tnow < temp)
	{
		philo->tnow = ft_gettimephl(philo);
		if (philo->tnow >= philo->final)
		{
			printf("%d durmiendo temp %ld tnow %ld y final %ld",philo->philo,temp, philo->tnow, philo->final);
			printf("\n\nPHILO %d HA MUERTO DURMIENDO\n\n", philo->philo);
			exit(1);
		}
	}
}

void	letsthink(t_philo *philo)
{
	printf("%ld philo %d pensando\n", philo->ms[0], philo->philo);
	while (philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
	{
		philo->tnow = ft_gettimephl(philo);
		if (philo->tnow >= philo->final)
		{
			printf("%d pensando tnow %ld y final %ld",philo->philo, philo->tnow, philo->final);
			printf("\n\nPHILO %d HA MUERTO PENSANDO\n\n", philo->philo);
			exit(1);
		}
		//usleep(500);
	}
}