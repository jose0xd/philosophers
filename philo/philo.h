/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:24:22 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/16 18:43:18 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_vars
{
	int		n_philo;
	int		time2die;
	int		time2eat;
	int		time2sleep;
	int		max_meals;
	int		death;
	long	init_time;
}	t_vars;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				num_meals;
	pthread_mutex_t	*fork_a;
	pthread_mutex_t	*fork_b;
	t_vars			*vars;
	pthread_t		thread;
}	t_philo;

int				ft_atoi(const char *str);
void			print_usage(void);
long			get_time(void);
void			ft_sleep(long time);
void			print_log(t_philo *philo, char *str);

t_vars			*init_vars(int ac, char **av);
pthread_mutex_t	*init_forks(int n_forks);
void			destroy_forks(pthread_mutex_t *forks, int n_forks);
t_philo			*init_philos(t_vars *vars, pthread_mutex_t *forks);

#endif
