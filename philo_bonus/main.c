/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:25:55 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/23 12:32:37 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "philo.h"

static void	loop(t_philo *philos)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < philos->vars->n_philo)
	{
		waitpid(-1, &ret, 0);
		if (WIFEXITED(ret))
		{
			i = -1;
			while (++i < philos->vars->n_philo)
				kill(philos[i].process, SIGKILL);
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	t_philo	*philos;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	sem_unlink("/forks");
	sem_unlink("/writer");
	vars->forks = sem_open("/forks", O_CREAT, 0644, vars->n_philo);
	vars->writer = sem_open("/writer", O_CREAT, 0644, 1);
	if (vars->forks == SEM_FAILED || vars->writer == SEM_FAILED)
	{
		free(vars);
		return (-1);
	}
	philos = init_philos(vars);
	loop(philos);
	sem_unlink("/forks");
	free(vars);
	free(philos);
}
