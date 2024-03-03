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
		printf("\n%sPHILO %d HA MUERTO%s\n", RED, philo->philo, RESET);
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
	printf("%s%ld tmls %sphilo %d%s comiendo%s\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
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
	printf("%s%ld tmls %sphilo %d%s durmiendo%s\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
}

void	letsthink(t_philo *philo)
{
	philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
	printf("%s%ld tmls %sphilo %d%s pensando\n",YELLOW,
		philo->ttotal, GREEN, philo->philo, RESET);
	while (philo->fork_l == NULL)
	{
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
	while (philo->fork->forktb != 0 || philo->fork_l->forktb != 0)
	{
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
}
