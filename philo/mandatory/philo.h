#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_forktb
{
    int				forktb;
    pthread_mutex_t	mutex_forktb;
}   t_forktb;

typedef struct s_philo
{
	struct timeval	time;
	int				philo;
	time_t			ttotal;
	time_t			*ms;
	int	die;
	int	slp;
	int	eat;
	time_t	td;
	time_t		cont;
	time_t		gone;
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

void	ft_init(t_table *table, char **argv, struct timeval	time);
void	ft_initphilos(t_table *table);
time_t	ft_gettime(t_table *table);
int	ft_atoi(const char *nptr);

#endif