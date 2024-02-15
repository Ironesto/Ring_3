# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_forktb
{
    int				forktb;
    pthread_mutex_t	mutex_forktb;
}   t_forktb;

typedef struct s_philo
{
	struct timeval	time;
	int	philo;
	time_t			ttotal;
	time_t			*ms;
	time_t			td;
	time_t			count;
	time_t	die;
	time_t	slp;
	time_t	eat;
	t_forktb	*fork;
	t_forktb	*fork_l;
	pthread_t	ph_thread;
}	t_philo;

typedef struct	s_table
{
	struct timeval	time;
	t_forktb	*forktb;
	t_philo		*philo;
	int	phl;
	time_t	tdie;
	time_t	teat;
	time_t	tslp;
	time_t	neat;
	time_t		*tz;
}	t_table;

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

void	ft_initphilos(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->phl)
	{
		table->philo[i].philo = i;
		table->philo[i].die = table->tdie;
		table->philo[i].td = ft_gettime(table) + table->tdie;
		table->philo[i].count = ft_gettime(table);
		table->philo[i].eat = table->teat;
		table->philo[i].slp = table->tslp;
		table->philo[i].ms = &table->tz[0];
		table->philo[i].fork = &table->forktb[i];
		if (i - 1 < 0)
			table->philo[i].fork_l = &table->forktb[table->phl - 1];
		else
			table->philo[i].fork_l = &table->forktb[i - 1];
		//agregar numero de comidas
		//printf("eat %ld die ,%ld, en %d\n",table->philo[i].count + table->philo[i].eat, table->philo[i].die, i);
		//printf("count %ld td ,%ld, en %d\n",table->philo[i].count, table->philo[i].td, i);
		i++;
	}
}

void	the_final(t_philo *philo)
{
	//philo->td = ft_gettimephl(philo);
	if (philo->count >= philo->td)
	{
		printf("\ntd :%ld", philo->td);
		printf("\n\nPHILO %d HA MUERTO\n", philo->philo);
		exit(1);
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
	table->tz[0] = ft_gettime(table);
	table->philo = malloc(sizeof(t_philo) * table->phl);
	table->forktb = malloc(sizeof(t_forktb) * table->phl);
	if(argv[5])
		table->neat = ft_atoi(argv[5]);
	while(i < table->phl)
	{
		pthread_mutex_init(&table->forktb[i].mutex_forktb, NULL);
		i++;
	}
	ft_initphilos(table);
}

void	eating(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->eat;
	pthread_mutex_lock(&philo->fork->mutex_forktb);
	pthread_mutex_lock(&philo->fork_l->mutex_forktb);
	philo->fork->forktb = 1;
	philo->fork_l->forktb = 1;
	printf("%ld tmls philo %d comiendo\n",philo->ttotal, philo->philo);
	//printf("%ld temp en phi %d y td %ld\n", temp, philo->philo, philo->td);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{	printf(" comida %ld contador %ld y td %ld", temp, philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);}
		usleep(500);
		the_final(philo);
	}
	philo->fork->forktb = 0;
	philo->fork_l->forktb = 0;
	pthread_mutex_unlock(&philo->fork->mutex_forktb);
	pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
}

void	sleeping(t_philo *philo)
{
	time_t	temp = philo->count + philo->slp;
	printf("%ld tmls philo %d durmiendo\n",philo->ttotal, philo->philo);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{	printf("durmiendo %ld contador %ld y td %ld", temp, philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);}
		usleep(500);
		the_final(philo);
	}
}

void	letsthink(t_philo *philo)
{
	printf("%ld tmls philo %d pensando\n",philo->ttotal, philo->philo);
	while(philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
	{
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{	printf("pensando  contador %ld y td %ld", philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);}
		usleep(500);
		the_final(philo);
	}
}

void	*routine(void *data)
{
	t_philo	*philo = (t_philo *)data;

	while(1)
	{
		//usleep(200);
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			eating(philo);
			sleeping(philo);
		}
		letsthink(philo);
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