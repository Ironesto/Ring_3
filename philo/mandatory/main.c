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

/* void	the_final(t_philo *philo)
{
	philo->td = ft_gettimephl(philo);
	if (philo->td >= philo->gone + philo->die)
	{
		printf("\n\nPHILO %d HA MUERTO\n", philo->philo);
		printf("%ld tiempo muerte\n\n", philo->td - philo->gone);
		exit(1);
	}
} */

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;
/* 	printf("philo %d, die %ld, eat %ld, sleep %ld tnow %ld\n",philo->philo, philo->tdie, philo->teat, philo->tslp, philo->tnow);
	printf("su fork es el %d y el de la izquierda %d\n",philo->fork->forktb, philo->fork_l->forktb); */
	while (1)
	{
		//usleep(2000);
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			letseat(philo);
			//usleep(500);
			letsleep(philo);
			//usleep(500);
		}
		if (philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
			letsthink(philo);
	}
}

void	ft_join(t_table *table)
{
	int i = 0;
	while (i < table->phl)
	{
		pthread_create(&table->philo[i].ph_thread, NULL, routine, &table->philo[i]);
		i++;
	}
	i = 0;
	while (i < table->phl)
	{	
		pthread_join(table->philo[i].ph_thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table			table;
	int				i;
	time_t	temp;

	i = 0;		//modificar muerte, añadir tiempo y pensar que mas hace falta cambiar
	ft_init(&table, argv);
	ft_join(&table);
/* 	while(i < table.phl)	//comprobar que todos los philos tengan los valores bien
	{
		printf("philo %d, die %ld, eat %ld, sleep %ld tnow %ld\n",table.philo[i].philo,table.philo[i].tdie, table.philo[i].teat, table.philo[i].tslp, table.philo[i].tnow);
		i++;
	} */

	//pthread_mutex_destroy(&counter.mutex_count);
	return (0);
}

// 1 microsegundo / 1000 = 1 milisegundo
// 1 segundo * 1000 = 1 milisegundo
// usleep(unsigned long int) suspende la ejecucion d eun programa durante x microsegundos