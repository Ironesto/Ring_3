#include "philo.h"

time_t	ft_gettime(t_table *table)
{
	gettimeofday(&table->time, NULL);
	return ((table->time.tv_sec * 1000) + (table->time.tv_usec / 1000));
}

time_t	ft_gettimephl(t_philo *table)
{
	gettimeofday(&table->time, NULL);
	return ((table->time.tv_sec * 1000) + (table->time.tv_usec / 1000));
}

void	the_final(t_philo *philo)
{
	philo->td = ft_gettimephl(philo);
	if (philo->td >= philo->gone + philo->die)
	{
		printf("\n\nPHILO %d HA MUERTO\n", philo->philo);
		printf("%ld tiempo muerte\n\n", philo->td - philo->gone);
		exit(1);
	}
}
void	usingforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork->mutex_forktb);
	pthread_mutex_lock(&philo->fork_l->mutex_forktb);
	philo->fork->forktb = 1;
	philo->fork_l->forktb = 1;
	philo->td = philo->cont;
	philo->cont = ft_gettimephl(philo);
	philo->gone = ft_gettimephl(philo);
	while (philo->cont <= philo->gone + philo->eat)
	{
		philo->cont = ft_gettimephl(philo);
		the_final(philo);
	}
	philo->td = ft_gettimephl(philo);
	printf("%ld tmls philo %d comiendo %ld \n",philo->ttotal, philo->philo, philo->cont - philo->gone);
	philo->fork->forktb = 0;
	philo->fork_l->forktb = 0;
	pthread_mutex_unlock(&philo->fork->mutex_forktb);
	pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
}

void	sleeping(t_philo *philo)
{
	philo->gone = ft_gettimephl(philo);
	printf("%ld tmls philo %d durmiendo %ld \n",philo->ttotal, philo->philo, philo->cont - philo->gone);
	while (philo->cont <= philo->gone + philo->slp)
	{
		philo->cont = ft_gettimephl(philo);
		the_final(philo);
	}
}

void	is_think(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
	{
		if (i == 0)
		{
			printf("%ld tmls philo %d pensando \n",philo->ttotal, philo->philo);
			i = 1;
		}
		the_final(philo);
	}
	
}

void	*routine(void *data)
{
	t_philo	*philo = (t_philo *)data;

	while(1)
	{
		philo->cont = ft_gettimephl(philo);
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		//printf("soy phil %d eat %d y %ld ms\n", philo->philo, philo->eat, philo->gone);
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			usingforks(philo);
			usleep(500);
			sleeping(philo);
			usleep(500);
			//comprobar muerte en sleep constante
		}
			is_think(philo);
			usleep(500);
			//comprobar muerte constantemente miestras piensa
		//usleep(500);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_table			table;
	int				i;
	time_t	temp;

	i = 0;
	ft_init(&table, argv, time);
	while (i < table.phl)
	{
		pthread_create(&table.philo[i].ph_thread, NULL, routine, &table.philo[i]);
		i++;
	}
	i = 0;
	while (i < table.phl)
	{	
		pthread_join(table.philo[i].ph_thread, NULL);
		i++;
	}
	//pthread_mutex_destroy(&counter.mutex_count);
	return (0);
}

// 1 microsegundo / 1000 = 1 milisegundo
// 1 segundo * 1000 = 1 milisegundo
// usleep(unsigned long int) suspende la ejecucion d eun programa durante x microsegundos