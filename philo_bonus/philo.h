/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:24:22 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/17 15:27:42 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <pthread.h>

typedef struct s_vars
{
	int			n_philo;
	int			time2die;
	int			time2eat;
	int			time2sleep;
	int			max_meals;
	int			death;
	long		init_time;
	pthread_t	watcher;
}	t_vars;

typedef struct s_philo
{
	int		id;
	long	last_meal;
	int		num_meals;
	sem_t	*forks;
	t_vars	*vars;
	pid_t	process;
}	t_philo;

int				ft_atoi(const char *str);
void			print_usage(void);
long			get_time(void);
void			ft_sleep(long time);
void			print_log(t_philo *philo, char *str);

t_vars			*init_vars(int ac, char **av);
t_philo			*init_philos(t_vars *vars, sem_t *forks);

#endif
