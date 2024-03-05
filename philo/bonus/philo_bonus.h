/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:05:32 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/04 17:05:32 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>

# define BOLD	 "\033[1m"
# define RED	 "\033[31;1m"
# define GREEN	 "\033[32;1m"
# define YELLOW	 "\033[33;1m"
# define CYAN	 "\033[36;1m"
# define BLUE	 "\033[34;1m"
# define BLACK	 "\033[30;1m"
# define MAGENTA "\033[35;1m"
# define WHITE	 "\033[37;1m"
# define RESET	 "\033[0m"

typedef struct s_forktb
{
	int				forktb;
	pthread_mutex_t	mutex_forktb;
}	t_forktb;

typedef struct s_philo
{
	struct timeval	time;
	int				philo;
	int				isdead;
	time_t			ttotal;
	time_t			ms;
	time_t			td;
	time_t			count;
	time_t			die;
	time_t			slp;
	time_t			eat;
	time_t			neat;
	sem_t			*sem_eat;
	pthread_t		ph_thread;
}	t_philo;

typedef struct s_table
{
	struct timeval	time;
	int				forks;
	int				*philo;
	int				phl;
	time_t			tdie;
	time_t			teat;
	time_t			tslp;
	time_t			neat;
	time_t			*tz;
	sem_t			*sem_eat;
}	t_table;

time_t	ft_gettime(t_table *table);
time_t	ft_gettimephl(t_philo *table);
int		ft_atoi(const char *nptr);
void	ft_join(t_table *table);
int		ft_atoi(const char *nptr);
int		routine(t_philo *philo);
void	the_final(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	letsthink(t_philo *philo);
void	*ft_compdead(void *data);
void	close_sem(t_table *table);
#endif