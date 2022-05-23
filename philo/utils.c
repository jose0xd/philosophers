/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:24:12 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/16 18:55:42 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
		num = num * 10 + (*str++ - '0');
	num *= sign;
	if (num != (int) num)
	{
		if (sign > 0)
			return (-1);
		return (0);
	}
	return ((int) num);
}

void	print_usage(void)
{
	printf("Usage: philo number_of_philosophers time_to_die\n");
	printf("             time_to_eat time_to_sleep\n");
	printf("             [number_of_times_each_philosopher_must_eat]\n");
}

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_sleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(50);
	}
}

void	print_log(t_philo *philo, char *str)
{
	printf("%ld %d %s\n",
		get_time() - philo->vars->init_time, philo->id, str);
}
