/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:10:59 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/02 20:11:45 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

time_t	ft_gettime(t_table *table)
{
	gettimeofday(&table->time, NULL);
	return ((table->time.tv_sec * 1000) + (table->time.tv_usec / 1000));
}

time_t	ft_gettimephl(t_philo *table)
{
	gettimeofday(&table->time, NULL);
	return ((table->time.tv_sec * 1000) + (table->time.tv_usec / 1000));
}

void	ft_join(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phl)
	{
		pthread_create(&table->philo[i].ph_thread,
			NULL, routine, &table->philo[i]);
		i++;
	}
	i = 0;
	while (i < table->phl)
	{
		pthread_join(table->philo[i].ph_thread, NULL);
		i++;
	}
}
