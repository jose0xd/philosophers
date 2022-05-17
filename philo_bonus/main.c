/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:25:55 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/17 15:15:48 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

int	main(int ac, char **av)
{
	t_vars	*vars;
	sem_t	*forks;
	t_philo	*philos;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	sem_unlink("/forks");
	forks = sem_open("/forks", O_CREAT, 0644, vars->n_philo);
	if (forks == SEM_FAILED)
	{
		free(vars);
		return (-1);
	}
	philos = init_philos(vars, forks);
	/*death_checker(philos);*/
	free(vars);
	sem_close(forks);
	free(philos);
}
