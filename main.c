/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:25:55 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/16 18:52:12 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"

void	death_checker(t_philo *philos)
{
	int	i;
	/*int	j;*/

	while (!philos->vars->death)
	{
		/*j = 0;*/
		i = -1;
		while (++i < philos->vars->n_philo)
		{
			if (get_time() - philos[i].last_meal > (long)philos[i].vars->time2die)
			{
				philos[i].vars->death = 1;
				print_log(&philos[i], "died");
				break ;
				/*if (philos->vars->max_meals && philos)*/
			}
			usleep(100);
		}
	}
}

int	main(int ac, char **av)
{
	t_vars			*vars;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	forks = init_forks(vars->n_philo);
	if (!forks)
	{
		free(vars);
		return (-1);
	}
	philos = init_philos(vars, forks);
	death_checker(philos);
	free(vars);
	destroy_forks(forks, vars->n_philo);
	free(philos);
}

/*
int	main(int ac, char **av)
{
	t_vars			*vars;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	//printf("n_philo: %d\n2die: %d\n2eat: %d\n2sleep: %d\nmax: %d\n",
			//vars->n_philo, vars->time2die, vars->time2eat,
			//vars->time2sleep, vars->max_meals);
	forks = init_forks(vars->n_philo);
	philos = init_philos(vars, forks);

	//sleep(3);
	while (!vars->death)
		usleep(100);

	free(vars);
	destroy_forks(forks, vars->n_philo);
	free(philos);
	//system("leaks philo");
}
*/
