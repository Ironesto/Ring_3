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
	time_t			td;
	time_t			count;
	time_t			die;
	time_t			slp;
	time_t			eat;
	t_forktb		*fork;
	t_forktb		*fork_l;
	pthread_t		ph_thread;
}	t_philo;

typedef struct	s_table
{
	struct timeval	time;
	t_forktb	*forktb;
	t_philo		*philo;
	int	phl;
	time_t	tdie;
	time_t	teat;
	time_t	tslp;
	time_t	neat;
	time_t		*tz;
}	t_table;


//void	ft_init(t_table *table, char **argv);
//void	ft_initphilos(t_table *table);
time_t	ft_gettime(t_table *table);
time_t	ft_gettimephl(t_philo *table);
int		ft_atoi(const char *nptr);
void	ft_join(t_table *table);
int		ft_atoi(const char *nptr);
void	*routine(void *data);

void	the_final(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	letsthink(t_philo *philo);
#endif