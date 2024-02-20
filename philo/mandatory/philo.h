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
}	t_forktb;

typedef struct s_ttotal
{
	int				ttotal;
	pthread_mutex_t	mutex_ttotal;
}	t_ttotal;

typedef struct s_philo
{
	struct timeval	time;
	int				philo;
	time_t			tnow;
	time_t			tdie;
	time_t			final;
	time_t			teat;
	time_t			tslp;
	time_t			neat;
	t_ttotal			*ttotal;
	time_t			*ms;
	t_forktb		*fork;
	t_forktb		*fork_l;
	pthread_t		ph_thread;
}	t_philo;

typedef struct s_table
{
	struct timeval	time;
	t_philo		*philo;
	t_forktb	*forktb;
	int			phl;
	time_t		tdie;
	time_t		teat;
	time_t		tslp;
	time_t		neat;
	t_ttotal		*ttotal;
	time_t		*tz;
}   t_table;


void	ft_init(t_table *table, char **argv);
void	ft_initphilos(t_table *table);
time_t	ft_gettime(t_table *table);
time_t	ft_gettimephl(t_philo *table);
int	ft_atoi(const char *nptr);

void	letseat(t_philo *philo);
void	letsleep(t_philo *philo);
void	letsthink(t_philo *philo);
#endif