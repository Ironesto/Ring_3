# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_forktb
{
	int				forktb;
	pthread_mutex_t	mutex_forktb;
}	t_forktb;

typedef struct s_philo
{
	struct timeval	time;
	int		philo;
	time_t		tnow;
	time_t		tdie;
	time_t		final;
	time_t		teat;
	time_t		tslp;
	time_t		neat;
	t_forktb		*fork;
	t_forktb		*fork_l;
	pthread_t		ph_thread;
}	t_philo;

typedef struct s_table
{
	t_philo		*philo;
	t_forktb	*forktb;
	int		phl;
	time_t	tdie;
	time_t	teat;
	time_t	tslp;
	time_t	neat;
}   t_table;

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



time_t	ft_gettimephl(t_philo *table)
{
	gettimeofday(&table->time, NULL);
	return ((table->time.tv_sec * 1000) + (table->time.tv_usec / 1000));
}

void	ft_initphilo(t_table *table)
{
	int	i = 0;

	while (i < table->phl)
	{
		table->philo[i].philo = i;
		table->philo[i].tnow = ft_gettimephl(&table->philo[i]);
		table->philo[i].tdie = table->tdie;
		table->philo[i].final = table->philo[i].tnow + table->tdie;
		table->philo[i].teat = table->teat;
		table->philo[i].tslp = table->tslp;
		table->philo[i].fork = &table->forktb[i];
		if (i - 1 < 0)
			table->philo[i].fork_l = &table->forktb[table->phl - 1];
		else
			table->philo[i].fork_l = &table->forktb[i - 1];
		i++;
	}
}

void	ft_init(t_table *table, char **argv)
{
	int	i;

	i = 0;
	table->phl = ft_atoi(argv[1]);
	table->tdie = ft_atoi(argv[2]);
	table->teat = ft_atoi(argv[3]);
	table->tslp = ft_atoi(argv[4]);
	table->philo = malloc((sizeof(t_philo) * table->phl));
	table->forktb = malloc((sizeof(t_forktb) * table->phl));
	while(i < table->phl)	// numera forks para debuguear
	{
		table->forktb[i].forktb = 0;
		i++;
	}
	i = 0;
	while(i < table->phl)
	{
		pthread_mutex_init(&table->forktb[i].mutex_forktb, NULL);
		i++;
	}
	ft_initphilo(table);
	//printf("philos %d, die %ld, eat %ld, sleep %ld\n",table->phl, table->tdie, table->teat, table->tslp);
}

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
	printf("philo %d esta comiendo\n", philo->philo);
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
	printf("philo %d esta durmiendo\n", philo->philo);
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
	printf("philo %d pensando\n",philo->philo);
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

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;
/* 	printf("philo %d, die %ld, eat %ld, sleep %ld tnow %ld\n",philo->philo, philo->tdie, philo->teat, philo->tslp, philo->tnow);
	printf("su fork es el %d y el de la izquierda %d\n",philo->fork->forktb, philo->fork_l->forktb); */
	while (1)
	{
		usleep(500);
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

	i = 0;
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