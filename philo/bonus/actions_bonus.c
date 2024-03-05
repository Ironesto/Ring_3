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

void	the_final(t_philo *philo)
{
	if (philo->count >= philo->td)
	{
		philo->isdead = 1;
		printf("\n%sPHILO %d HA MUERTO%s\n", RED, philo->philo, RESET);
		exit(1);
	}
}

void	eating(t_philo *philo)
{
	time_t	temp;

	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s pensando\n", CYAN,
			philo->ttotal, GREEN, philo->philo, RESET);
	sem_wait(philo->sem_eat);
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s comiendo%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, BLUE, RESET);
	philo->td = philo->count + philo->die;
	temp = philo->count + philo->eat;
	while (philo->count < temp)
	{
	}
	sem_post(philo->sem_eat);
}

void	sleeping(t_philo *philo)
{
	time_t	temp;

	temp = philo->count + philo->slp;
	philo->ttotal = ft_gettimephl(philo) - philo->ms;
	if (philo->isdead == 0)
		printf("%s%ld tmls %sphilo %d%s durmiendo%s\n", CYAN,
			philo->ttotal, GREEN, philo->philo, MAGENTA, RESET);
	while (philo->count < temp)
	{
	}
}

int	routine(t_philo *philo)
{
	while (1 && philo->neat > 0)
	{
		pthread_create(&philo->ph_thread,
			NULL, ft_compdead, philo);
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		eating(philo);
		if (philo->neat)
			philo->neat--;
		if (philo->neat == 0)
			break ;
		philo->ttotal = ft_gettimephl(philo) - philo->ms;
		sleeping(philo);
	}
	return (0);
}
