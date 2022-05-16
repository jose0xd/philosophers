/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:32:14 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/16 21:12:19 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

static void	*eat(void *args)
{
	t_philo	*philo;

	philo = args;
	while (!philo->vars->death)
	{
		pthread_mutex_lock(philo->fork_a);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_b);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		philo->last_meal = get_time();
		philo->num_meals++;
		ft_sleep(philo->vars->time2eat);
		pthread_mutex_unlock(philo->fork_a);
		pthread_mutex_unlock(philo->fork_b);
		print_log(philo, "is sleeping");
		ft_sleep(philo->vars->time2sleep);
		print_log(philo, "is thinking");
	}
	return (NULL);
}

// TODO check input
t_vars	*init_vars(int ac, char **av)
{
	t_vars			*vars;

	if (ac != 5 && ac != 6)
	{
		print_usage();
		return (NULL);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->n_philo = ft_atoi(av[1]);
	vars->time2die = ft_atoi(av[2]);
	vars->time2eat = ft_atoi(av[3]);
	vars->time2sleep = ft_atoi(av[4]);
	if (ac == 6)
		vars->max_meals = ft_atoi(av[5]);
	else
		vars->max_meals = 0;
	vars->death = 0;
	vars->init_time = get_time();
	return (vars);
}

pthread_mutex_t	*init_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(n_forks * sizeof(pthread_mutex_t));
	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (NULL);
	}
	return (forks);
}

void	destroy_forks(pthread_mutex_t *forks, int n_forks)
{
	while (--n_forks >= 0)
		pthread_mutex_destroy(&forks[n_forks]);
	free(forks);
}

t_philo	*init_philos(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(vars->n_philo * sizeof(t_philo));
	i = -1;
	while (++i < vars->n_philo)
	{
		philos[i].id = i;
		philos[i].last_meal = vars->init_time;
		philos[i].num_meals = 0;
		philos[i].fork_a = &forks[i];
		philos[i].fork_b = &forks[(i + 1) % vars->n_philo];
		if (i % 2 == 1)
		{
			philos[i].fork_a = philos[i].fork_b;
			philos[i].fork_b = &forks[i];
		}
		philos[i].vars = vars;
		pthread_create(&(philos[i].thread), NULL, eat, &philos[i]);
	}
	return (philos);
}
