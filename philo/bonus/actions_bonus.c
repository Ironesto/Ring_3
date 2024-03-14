/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:06:06 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/04 17:06:06 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	the_final(t_philo *philo)
{
	if (philo->count >= philo->td)
	{
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		printf("%s%ld %d DIED%s\n",
			RED, philo->ttotal, philo->philo, RESET);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	time_t	temp;

	if (philo->isdead == 0)
		printf("%s%ld %s%d%s is thinking\n", CYAN,
			philo->ttotal, GREEN, philo->philo, RESET);
	else
		return (1);
	sem_wait(philo->sem_eat);
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
	{
		usleep(200);
		printf("%s%ld %s%d%s has taken a fork%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, YELLOW, RESET);
		printf("%s%ld %s%d%s has taken a fork%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, YELLOW, RESET);
		printf("%s%ld %s%d%s is eating%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	}
	else
		return (1);
	philo->td = philo->count + philo->die;
	temp = philo->count + philo->eat;
	while (philo->count < temp)
	{
	}
	sem_post(philo->sem_eat);
	return (0);
}

int	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
		printf("%s%ld %s%d%s is sleeping%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	else
		return (1);
	while (philo->count < temp)
	{
	}
	return (0);
}

int	routine(t_philo *philo)
{
	pthread_create(&philo->ph_thread,
		NULL, ft_compdead, philo);
	while (1 && philo->neat > 0)
	{
		usleep(500);
		if (philo->isdead == 1)
			return (1);
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		eating(philo);
		if (philo->neat)
			philo->neat--;
		if (philo->neat == 0)
			return (0);
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		sleeping(philo);
	}
	return (0);
}
