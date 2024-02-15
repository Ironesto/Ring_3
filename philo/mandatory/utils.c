#include "philo.h"

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

void	ft_initphilos(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->phl)
	{
		table->philo[i].philo = i;
		table->philo[i].gone = ft_gettime(table);
		table->philo[i].td = 0;
		table->philo[i].die = table->tdie;
		table->philo[i].eat = table->teat;
		table->philo[i].slp = table->tslp;
		table->philo[i].ms = &table->tz[0];
		table->philo[i].cont = ft_gettime(table);
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
