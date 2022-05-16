#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

void	*eat(void *args);

typedef struct s_vars
{
	int	n_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	max_meals;
	int	death;
	int	init_time;
}	t_vars;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	pthread_mutex_t	*fork_a;
	pthread_mutex_t	*fork_b;
	t_vars			*vars;
	pthread_t		thread;
}	t_philo;

static void	print_usage(void)
{
	printf("Usage: philo number_of_philosophers time_to_die\n");
	printf("             time_to_eat time_to_sleep\n");
	printf("             [number_of_times_each_philosopher_must_eat]\n");
}

int	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

// TODO check input
static t_vars	*init_vars(int ac, char **av)
{
	t_vars			*vars;

	if (ac != 5 && ac !=6)
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

static pthread_mutex_t	*init_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(n_forks * sizeof(pthread_mutex_t));
	i = 0;
	while (i < n_forks)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

static void	destroy_forks(pthread_mutex_t *forks, int n_forks)
{
	while (--n_forks >= 0)
		pthread_mutex_destroy(&forks[n_forks]);
	free(forks);
}

static t_philo	*init_philos(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(vars->n_philo * sizeof(t_philo));
	i = -1;
	while (++i < vars->n_philo)
	{
		philos[i].id = i;
		philos[i].last_meal = 0;
		philos[i].fork_a = &forks[i];
		philos[i].fork_b = &forks[(i + 1) % vars->n_philo];
		if (i == vars->n_philo - 1)
		{
			philos[i].fork_a = philos[i].fork_b;
			philos[i].fork_b = &forks[i];
		}
		philos[i].vars = vars;
		pthread_create(&(philos[i].thread), NULL, eat, &philos[i]);
	}
	return (philos);
}

void	*eat(void *args)
{
	t_philo	*philo;

	philo = args;
	while (42)
	{
		pthread_mutex_lock(philo->fork_a);
		printf("Philosopher %d take a fork.\n", philo->id);
		pthread_mutex_lock(philo->fork_b);
		printf("Philosopher %d take a fork.\n", philo->id);
		printf("Philosopher %d is eating...\n", philo->id);
		philo->last_meal = get_time();
		usleep(philo->vars->time2eat * 1000);
		pthread_mutex_unlock(philo->fork_a);
		pthread_mutex_unlock(philo->fork_b);
		printf("Philosopher %d is sleeping...\n", philo->id);
		usleep(philo->vars->time2sleep * 1000);
		printf("Philosopher %d is thinking...\n", philo->id);
		if (get_time() - philo->last_meal > philo->vars->time2die)
		{
			printf("Philosopher %d died\n", philo->id);
			philo->vars->death = 1;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_vars			*vars;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	/*printf("n_philo: %d\n2die: %ld\n2eat: %ld\n2sleep: %ld\nmax: %d\n",*/
			/*vars->n_philo, vars->time2die, vars->time2eat, vars->time2sleep, vars->max_meals);*/
	forks = init_forks(vars->n_philo);
	philos = init_philos(vars, forks);

	/*sleep(3);*/
	while (!vars->death)
		usleep(100);

	free(vars);
	destroy_forks(forks, vars->n_philo);
	free(philos);
	/*system("leaks philo");*/
}
