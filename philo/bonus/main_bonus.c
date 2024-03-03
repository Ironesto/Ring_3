#include "philo_bonus.h"

t_philo	ft_initphilos(t_table *table, int i)
{
	t_philo	philo;

	philo.philo = i;
	philo.die = table->tdie;
	if(table->neat)
		philo.neat = table->neat;
	philo.td = ft_gettime(table) + table->tdie;
	philo.count = ft_gettime(table);
	philo.eat = table->teat;
	philo.slp = table->tslp;
	philo.ms = &table->tz[0];
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
	table->tz[0] = ft_gettime(table);
	table->sem_eat = sem_open("/forks", O_CREAT, 0644, table->phl / 2);
    table->forks = table->phl;
	if (argv[5])
		table->neat = ft_atoi(argv[5]);
	//ft_initphilos(table);
}

void	*routine(t_philo *philo)
{
	while (1 && philo->neat > 0)
	{
		//usleep(500);
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->sem_eat == 0)
			letsthink(philo);
		if (philo->sem_eat)
		{
			eating(philo);
			//usleep(500);
			philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
			sleeping(philo);
			//usleep(500);
		}
		if (philo->sem_eat == 0)
			letsthink(philo);
		if (philo->neat)
			philo->neat--;
	}
	return (NULL);
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
	int		pid;
	t_philo	philo;
	int		status;

	if (ft_validargs(argc, argv) == 1)
		return (1);
	ft_init(&table, argv);
	//creacion de hijos
	i = 0;
	while (i < argc)
	{
		pid = fork();
		if (pid == 0)
		{
			philo = ft_initphilos(&table, i);
			//routine(&philo);
		}
		i++;
	}
	waitpid(0, &status, 0);
	close_sem(&table);
    return (0);
}