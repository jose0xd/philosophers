/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:32:14 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/23 12:24:18 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

static void	*death_checker(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (!philo->vars->death)
	{
		if (get_time() - philo->last_meal > philo->vars->time2die)
		{
			philo->vars->death = 1;
			print_log(philo, "died");
			sem_wait(philo->vars->writer);
			exit(1);
		}
		if (philo->vars->max_meals
			&& philo->num_meals >= philo->vars->max_meals)
			break ;
		usleep(100);
	}
	return (NULL);
}

static void	*eat(t_philo *philo)
{
	pthread_create(&philo->watcher, NULL, death_checker, philo);
	if (philo->id % 2)
		ft_sleep(1);
	while (!philo->vars->death)
	{
		sem_wait(philo->vars->forks);
		print_log(philo, "has taken a fork");
		sem_wait(philo->vars->forks);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		philo->last_meal = get_time();
		philo->num_meals++;
		ft_sleep(philo->vars->time2eat);
		sem_post(philo->vars->forks);
		sem_post(philo->vars->forks);
		if (philo->vars->max_meals
			&& philo->num_meals >= philo->vars->max_meals)
			break ;
		print_log(philo, "is sleeping");
		ft_sleep(philo->vars->time2sleep);
		print_log(philo, "is thinking");
	}
	if (philo->vars->death)
		exit(1);
	exit(0);
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

t_philo	*init_philos(t_vars *vars)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(vars->n_philo * sizeof(t_philo));
	i = -1;
	while (++i < vars->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = vars->init_time;
		philos[i].num_meals = 0;
		philos[i].vars = vars;
		philos[i].process = fork();
		if (philos[i].process == 0)
			eat(&philos[i]);
	}
	return (philos);
}
