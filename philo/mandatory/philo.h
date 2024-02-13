#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_time
{
	int	philo;
	int	die;
	int	slp;
	int	eat;
}	t_time;



#endif