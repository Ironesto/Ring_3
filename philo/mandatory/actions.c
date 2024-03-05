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
		printf("\n%sPHILO %d HA MUERTO %ld ms%s\n",
			RED, philo->philo, philo->ttotal, RESET);
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
	printf("%s%ld tmls %sphilo %d%s comiendo%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	philo->td = philo->count + philo->die;
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(1000);
		if (philo->count >= philo->td)
			puts("comiendo");
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
	printf("%s%ld tmls %sphilo %d%s durmiendo%s\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{
		philo->count = ft_gettimephl(philo);
		usleep(1000);
		if (philo->count >= philo->td)
			puts("durmiendo");
		the_final(philo);
	}
}

void	letsthink(t_philo *philo)
{
	philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
	printf("%s%ld tmls %sphilo %d%s pensando\n", YELLOW,
		philo->ttotal, GREEN, philo->philo, RESET);
	while (philo->fork_l == NULL)
	{
		philo->count = ft_gettimephl(philo);
		the_final(philo);
	}
	while (philo->fork->forktb != 0 || philo->fork_l->forktb != 0)
	{
		philo->count = ft_gettimephl(philo);
		usleep(1000);
		if (philo->count >= philo->td)
			puts("pensando");
		the_final(philo);
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while ((1 && philo->neat > 0) || philo->neat == -1)
	{
		philo->ttotal = ft_gettimephl(philo) - philo->ms[0];
		if (philo->fork_l == NULL)
			letsthink(philo);
		if (philo->fork->forktb == 0 && philo->fork_l->forktb == 0)
		{
			ft_haveforks(philo);
		}
		if (philo->fork->forktb != 0 || philo->fork_l->forktb != 0)
			letsthink(philo);
	}
	return (NULL);
}
