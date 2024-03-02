/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:13:24 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/02 20:13:24 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_final(t_philo *philo)
{
	if (philo->count >= philo->td)
	{
		printf("\nPHILO %d HA MUERTO\n", philo->philo);
		exit(1);
	}
}

void	eating(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->eat;
	pthread_mutex_lock(&philo->fork->mutex_forktb);
	pthread_mutex_lock(&philo->fork_l->mutex_forktb);
	philo->fork->forktb = 1;
	philo->fork_l->forktb = 1;
	printf("%ld tmls philo %d comiendo\n", philo->ttotal, philo->philo);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		usleep(500);
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{
			printf(" comida %ld contador %ld y td %ld", temp, philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);
		}
		the_final(philo);
	}
	philo->fork->forktb = 0;
	philo->fork_l->forktb = 0;
	pthread_mutex_unlock(&philo->fork->mutex_forktb);
	pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
}

void	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	printf("%ld tmls philo %d durmiendo\n", philo->ttotal, philo->philo);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{
			printf("durmiendo %ld contador %ld y td %ld", temp, philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);
		}
		usleep(500);
		the_final(philo);
	}
}

void	letsthink(t_philo *philo)
{
	philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
	printf("%ld tmls philo %d pensando\n", philo->ttotal, philo->philo);
	while (philo->fork->forktb != 0 && philo->fork_l->forktb != 0)
	{
		philo->count = ft_gettimephl(philo);
		if (philo->count >= philo->td)
		{
			printf("\npensando  contador %ld y td %ld", philo->count, philo->td);
			printf("\nvalor al entrar x en philo %d\n", philo->philo);
		}
		the_final(philo);
	}
	usleep(500);
}
