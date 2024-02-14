#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_forktb
{
    int             forktb;
    pthread_mutex_t	mutex_forktb;
}   t_forktb;

typedef struct s_philo
{
	struct timeval	time;
	int	philo;
	time_t		*ms;
	int	die;
	int	slp;
	int	eat;
	t_forktb	*fork;
	t_forktb	*fork_l;
	pthread_t	ph_thread;
}	t_philo;

typedef struct	s_table
{
	struct timeval	time;
	t_forktb	*forktb;
	t_philo		*philo;
	int	phl;
	int	tdie;
	int	teat;
	int	tslp;
	int	neat;
	time_t		*tz;
}	t_table;

int	ft_atoi(const char *nptr);

#endif