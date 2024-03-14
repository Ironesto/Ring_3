/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:44:30 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/13 19:44:30 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_leaks(void)
{
	system("leaks -q philo");
}

t_philo	ft_initphilos(t_table *table, int i)
{
	t_philo	philo;

	philo.philo = i;
	philo.isdead = 0;
	philo.die = table->tdie;
	if (table->neat)
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
}

void *ft_compdead(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->count < philo->td)
	{
		usleep(1000);
		philo->count = ft_gettimephl(philo);
		if (the_final(philo) == 1)
		{
			philo->isdead = 1;
			exit (1);
		}
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
		while (argv[i][k])
		{
			if ((argv[i][k] < '0' || argv[i][k] > '9') && argv[i][k] != '+' && argv[i][k] != '-')
				return (write(2, "Invalid arguments\n", 18), 1);
			if (ft_atoi(argv[1]) <= 0 && k == '\0')
				return (write(2, "Must be 1 or more\n", 18), 1);
			k++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;
	t_philo	philo;

	//atexit(ft_leaks);
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
	close_sem(&table);
	return (0);
}
