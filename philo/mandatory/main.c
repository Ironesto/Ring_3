/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:13:21 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/02 20:17:17 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initphilos(t_table *table)
{
	int	i;
	i = 0;
	while (i < table->phl)
	{
		table->philo[i].philo = i;
		table->philo[i].die = table->tdie;
		if(table->neat)
			table->philo[i].neat = table->neat;
		table->philo[i].td = ft_gettime(table) + table->tdie;
		table->philo[i].count = ft_gettime(table);
		table->philo[i].eat = table->teat;
		table->philo[i].slp = table->tslp;
		table->philo[i].ms = &table->tz[0];
		table->philo[i].fork = &table->forktb[i];
		if (table->phl == 1)
			table->philo[0].fork_l = NULL;
		else if (i - 1 < 0)
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
	table->tz = malloc(sizeof(time_t));
	table->tz[0] = ft_gettime(table);
	table->philo = malloc(sizeof(t_philo) * table->phl);
	table->forktb = malloc(sizeof(t_forktb) * table->phl);
	while (i < table->phl)
	{
		table->forktb[i].forktb = 0;
		i++;
	}
	i = 0;
	if (argv[5])
		table->neat = ft_atoi(argv[5]);
	while (i < table->phl)
	{
		pthread_mutex_init(&table->forktb[i].mutex_forktb, NULL);
		i++;
	}
	ft_initphilos(table);
}

void	*routine(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;

	while (1 && philo->neat > 0)
	{
		//usleep(500);
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->fork_l == NULL)
			letsthink(philo);
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			eating(philo);
			//usleep(500);
			philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
			sleeping(philo);
			//usleep(500);
		}
		if (philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
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

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (ft_validargs(argc, argv) == 1)
		return (1);
	i = -1;
	ft_init(&table, argv);
	while (++i < table.phl)
		pthread_create(&table.philo[i].ph_thread,
			NULL, routine, &table.philo[i]);
	i = -1;
	while (++i < table.phl)
		pthread_join(table.philo[i].ph_thread, NULL);
	i = -1;
	while (++i < table.phl)
		pthread_mutex_destroy(&table.forktb[i].mutex_forktb);
	return (0);
}
