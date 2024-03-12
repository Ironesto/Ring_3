/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:11:53 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/02 20:13:12 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

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
	int				*sd;
	time_t			ttotal;
	time_t			*ms;
	time_t			td;
	time_t			count;
	time_t			die;
	time_t			slp;
	time_t			eat;
	time_t			neat;
	t_forktb		*fork;
	t_forktb		*fork_l;
	pthread_t		ph_thread;
}	t_philo;

typedef struct s_table
{
	struct timeval	time;
	t_forktb		*forktb;
	t_philo			*philo;
	int				phl;
	int				*isdead;
	int				forks;
	time_t			tdie;
	time_t			teat;
	time_t			tslp;
	time_t			neat;
	time_t			*tz;
}	t_table;

time_t	ft_gettime(t_table *table);
time_t	ft_gettimephl(t_philo *table);
int		ft_atoi(const char *nptr);
void	ft_join(t_table *table);
int		ft_atoi(const char *nptr);
int		ft_validargs(int argc, char **argv);
void	*routine(void *data);
int		ft_haveforks(t_philo *philo);
int		the_final(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		letsthink(t_philo *philo);
void	print_eating(t_philo *philo);
void	forksandneats(t_table *table, char **argv);
#endif