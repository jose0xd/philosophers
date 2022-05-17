/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:32:14 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/17 19:07:32 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "philo.h"

#include <stdio.h>

static void	*death_checker(void *void_philos)
{
	int		i;
	int		j;
	t_philo	*philos;

	philos = void_philos;
	while (!philos->vars->death)
	{
		j = 0;
		i = -1;
		while (++i < philos->vars->n_philo)
		{
			/*if (get_time() - philos[i].last_meal > philos->vars->time2die)*/
			/*{*/
				/*philos->vars->death = 1;*/
				/*print_log(&philos[i], "died");*/
				/*break ;*/
			/*}*/
			if (philos->vars->max_meals
				&& philos[i].num_meals >= philos->vars->max_meals)
				j++;
			usleep(100);
		}
		if (j == philos->vars->n_philo)
			break ;
	}
	return (NULL);
}

static void	*eat(t_philo *philo)
{
	pthread_create(&philo->vars->watcher, NULL, death_checker, philo);
	if (philo->id % 2)
		ft_sleep(1);
	while (!philo->vars->death)
	{
		sem_wait(philo->forks);
		print_log(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		philo->last_meal = get_time();
		philo->num_meals++;
		ft_sleep(philo->vars->time2eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		print_log(philo, "is sleeping");
		ft_sleep(philo->vars->time2sleep);
		print_log(philo, "is thinking");
	}
	exit(0);
	/*return (NULL);*/
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

t_philo	*init_philos(t_vars *vars, sem_t *forks)
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
		philos[i].forks = forks;
		philos[i].vars = vars;
		philos[i].process = fork();
		if (philos[i].process == 0)
			eat(&philos[i]);
	}
	ft_sleep(5000);
	/*waitpid(-1, &i, 0);*/
	i = -1;
	while (++i < vars->n_philo)
	{
		kill(philos[i].process, SIGKILL);
	}
	return (philos);
}
