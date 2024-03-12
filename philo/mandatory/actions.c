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

int	the_final(t_philo *philo)
{
	if (philo->sd[0] == 1)
		return (1);
	if (philo->count >= philo->td)
	{
		philo->sd[0] = 1;
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		printf("%s%ld %d DIED%s\n",
			RED, philo->ttotal, philo->philo, RESET);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->eat;
	pthread_mutex_lock(&philo->fork->mutex_forktb);
	pthread_mutex_lock(&philo->fork_l->mutex_forktb);
	philo->fork->forktb = 1;
	philo->fork_l->forktb = 1;
	print_eating(philo);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(500);
		if (the_final(philo) == 1)
			return (1);
	}
	philo->fork->forktb = 0;
	philo->fork_l->forktb = 0;
	pthread_mutex_unlock(&philo->fork->mutex_forktb);
	pthread_mutex_unlock(&philo->fork_l->mutex_forktb);
	return (0);
}

int	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	printf("%s%ld %s%d%s is sleeping%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(500);
		if (the_final(philo) == 1)
			return (1);
	}
	return (0);
}

int	letsthink(t_philo *philo)
{
	philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
	printf("%s%ld %s%d%s is thinking\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, RESET);
	while (philo->fork_l == NULL)
	{
		usleep(500);
		philo->count = ft_gettimephl(philo);
		if (the_final(philo) == 1)
			return (1);
	}
	while (philo->fork->forktb != 0 || philo->fork_l->forktb != 0)
	{
		philo->count = ft_gettimephl(philo);
		usleep(500);
		if (the_final(philo) == 1)
			return (1);
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while ((1 && philo->neat > 0) || philo->neat == -1)
	{
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->fork_l == NULL)
			if (letsthink(philo) == 1)
				return (NULL);
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			if (ft_haveforks(philo) == 1)
				return (NULL);
		}
		if (philo->fork->forktb != 0 || philo->fork_l->forktb != 0)
			if (letsthink(philo) == 1)
				return (NULL);
	}
	return (NULL);
}
