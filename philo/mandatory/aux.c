/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:48:05 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/12 19:51:57 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eating(t_philo *philo)
{
	printf("%s%ld %s%d%s has taken a fork%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, CYAN, RESET);
	printf("%s%ld %s%d%s has taken a fork%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, CYAN, RESET);
	printf("%s%ld %s%d%s is eating%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, BLUE, RESET);
}

void	forksandneats(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (i < table->phl)
	{
		table->forktb[i].forktb = 0;
		i++;
	}
	i = -1;
	if (argv[5] != NULL)
		table->neat = ft_atoi(argv[5]);
	else
		table->neat = -1;
	while (++i < table->phl)
		pthread_mutex_init(&table->forktb[i].mutex_forktb, NULL);
}
