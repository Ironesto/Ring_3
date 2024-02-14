#include "philo.h"

void	ft_gettime(struct timeval time, int sec, t_table *table)
{
	gettimeofday(&time, NULL);
	table->tz[0] = (time.tv_sec - sec) * 1000 + (time.tv_usec / 1000);
}

void	ft_initphilos(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->phl)
	{
		table->philo[i].philo = i;
		table->philo[i].die = table->tdie;
		table->philo[i].eat = table->teat;
		table->philo[i].slp = table->tslp;
		table->philo[i].ms = &table->tz[0];
		table->philo[i].fork = &table->forktb[i];
		if (i - 1 < 0)
			table->philo[i].fork_l = &table->forktb[table->phl - 1];
		else
			table->philo[i].fork_l = &table->forktb[i - 1];
		//agregar numero de comidas
		i++;
	}
}


void	ft_init(t_table *table, char **argv, struct timeval	time)
{
	int i = 0;


	table->phl = ft_atoi(argv[1]);
	table->tdie = ft_atoi(argv[2]);
	table->teat = ft_atoi(argv[3]);
	table->tslp = ft_atoi(argv[4]);
	table->tz = malloc(sizeof(time_t));
	table->philo = malloc(sizeof(t_philo) * table->phl);
	table->forktb = malloc(sizeof(t_forktb) * table->phl);
	if(argv[5])
		table->neat = ft_atoi(argv[5]);
/* 	while(i < table->phl)
	{
		table->fork[i] = i;
		i++;
	} */
	ft_initphilos(table);

}

void	*routine(void *data)
{
	t_philo	*philo = (t_philo *)data;
	gettimeofday(&philo->time, NULL);
	//printf("philo nº = %d con fork %d y left fork %d\n", philo->philo, philo->fork->forktb, philo->fork_l->forktb);
	printf("philo nº %d: %ld ms antes\n",philo->philo, philo->ms[0]);
	if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)		//aqui come
	{
		pthread_mutex_lock(&philo->fork->mutex_forktb);
		pthread_mutex_lock(&philo->fork_l->mutex_forktb);
		//puts("tiene");
		philo->fork->forktb = 1;
		philo->fork_l->forktb = 1;
		printf("philo nº %d: %ld ms comiendo\n",philo->philo, philo->ms[0]);
		usleep(philo->eat * 1000);
		philo->fork->forktb = 0;
		philo->fork_l->forktb = 0;
		pthread_mutex_unlock(&philo->fork->mutex_forktb);
		pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
	}
	printf("philo nº %d: %ld ms despues\n",philo->philo, philo->ms[0]);
/* 	else if (philo->fork->forktb == 1)
		philo->fork->forktb == 0; */
	//printf("philo nº %d: estado del tenedor %d\n", philo->philo, philo->fork->forktb);
/* 	if (fork == TRUE)
		eat(usleep(time eat * 1000) && time to die = 0);
		sleep(time to die += time to sleep);
	else
	{
		think(time to die += time to think);
		comp dead;
	} */
	//pthread_mutex_lock(&table->counter.mutex_count);
/* 	if (table->fork[0] == 0)
		table->fork[0] = 1;
	else
		table->fork[0] = 0; */
	//pthread_mutex_unlock(&table->counter.mutex_count);
/* 	printf("fork : %d\n", table->fork[0]);
	if (table->fork[0] == 0)
	{
		printf("HE DIED %ldms\n", table->tz);
	}
	else
		printf("HE LIVES %ldms\n", table->tz); */
	return (NULL);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_table			table;
	int				i;

	i = 0;
	ft_init(&table, argv, time);
	gettimeofday(&time, NULL);
	//pthread_mutex_init(&counter.mutex_count, NULL);
	while (1)
	{
		//printf("%ld mls\n", ft_gettime(time, time.tv_sec));
		ft_gettime(time, time.tv_sec, &table);
		pthread_create(&table.philo[i].ph_thread, NULL, routine, &table.philo[i]);
		//pthread_join(table.philo[i].ph_thread, NULL);
		i++;
		if (i == table.phl)
			i = 0;
		usleep(1 * 350000);
	}
	//pthread_mutex_destroy(&counter.mutex_count);
	return (0);
}

// 1 microsegundo / 1000 = 1 milisegundo
// 1 segundo * 1000 = 1 milisegundo
// usleep(unsigned long int) suspende la ejecucion d eun programa durante x microsegundos