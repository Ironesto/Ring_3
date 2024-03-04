#include "philo_bonus.h"

t_philo	ft_initphilos(t_table *table, int i)
{
	t_philo	philo;

	philo.philo = i;
	philo.isdead = 0;
	philo.die = table->tdie;
	if(table->neat)
		philo.neat = table->neat;
	philo.td = ft_gettime(table) + table->tdie;
	philo.count = ft_gettime(table);
	philo.eat = table->teat;
	philo.slp = table->tslp;
	philo.ms = ft_gettime(table);
	philo.sem_eat = table->sem_eat;
	return (philo);
}

void	ft_init(t_table *table, char **argv)
{
	sem_unlink("/forks");
	table->phl = ft_atoi(argv[1]);
	table->tdie = ft_atoi(argv[2]);
	table->teat = ft_atoi(argv[3]);
	table->tslp = ft_atoi(argv[4]);
	table->tz = malloc(sizeof(time_t));
	table->philo = malloc(sizeof(int) * table->phl);
	table->tz[0] = ft_gettime(table);
    table->forks = table->phl / 2;
	table->sem_eat = sem_open("/forks", O_CREAT, 0644, table->forks);
	if (argv[5])
		table->neat = ft_atoi(argv[5]);
	//ft_initphilos(table);
}

void	*ft_compdead(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;
	
	while (philo->count < philo->td)
	{
		usleep(1000);
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
	return (NULL);
}

int	routine(t_philo *philo)
{
	while (1 && philo->neat > 0)
	{
		pthread_create(&philo->ph_thread,
			NULL, ft_compdead, philo);
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		eating(philo);
		if (philo->neat)
			philo->neat--;
		if (philo->neat == 0)
			break ;
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		sleeping(philo);
	}
	return (0);
}

int	ft_validargs(int argc, char **argv)
{
	int	i;
	int	k;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments\n", 26), 1);
	while (++i < argc)
	{
		k = 0;
		while(argv[i][k])
		{
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (write(2, "Invalid arguments\n", 18), 1);
			k++;
		}
	}
	return (0);
}

void	close_sem(t_table *table)
{
	sem_unlink("/forks");
	sem_close(table->sem_eat);
}

int main(int argc, char **argv)
{
	t_table	table;
	int		i;
	t_philo	philo;
	int		status;

	if (ft_validargs(argc, argv) == 1)
		return (1);
	ft_init(&table, argv);
	i = 0;
	while (i < table.phl)
	{
		table.philo[i] = fork();
		if (table.philo[i] == 0)
		{
			philo = ft_initphilos(&table, i);
			routine(&philo);
			break ;
		}
		i++;
	}
	i = 0;
	if (waitpid(0, &status, 0) > 0)
		while (i < table.phl)
		{
			kill(table.philo[i], 9);
			i++;
		}
	close_sem(&table);
    return (0);
}