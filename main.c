#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

typedef struct s_vars
{
	int		n_philo;
	long	time2die;
	long	time2eat;
	long	time2sleep;
	int		max_meals;
}	t_vars;

static void	print_usage(void)
{
	printf("Usage: philo number_of_philosophers time_to_die\n");
	printf("             time_to_eat time_to_sleep\n");
	printf("             [number_of_times_each_philosopher_must_eat]\n");
}

// TODO check input
static t_vars	*init_vars(int ac, char **av)
{
	t_vars	*vars;

	if (ac != 5 && ac !=6)
	{
		print_usage();
		return (NULL);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->n_philo = ft_atoi(av[1]);
	vars->time2die = (long)ft_atoi(av[2]);
	vars->time2eat = (long)ft_atoi(av[3]);
	vars->time2sleep = (long)ft_atoi(av[4]);
	if (ac == 6)
		vars->max_meals = ft_atoi(av[5]);
	else
		vars->max_meals = 0;
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
}

/*void	*eat(void *args)*/
/*{*/

/*}*/

int	main(int ac, char **av)
{
	t_vars			*vars;
	pthread_mutex_t	*forks;

	vars = init_vars(ac, av);
	if (!vars)
		return (0);
	/*printf("n_philo: %d\n2die: %ld\n2eat: %ld\n2sleep: %ld\nmax: %d\n",*/
			/*vars->n_philo, vars->time2die, vars->time2eat, vars->time2sleep, vars->max_meals);*/
	forks = init_forks(vars->n_philo);


	destroy_forks(forks, vars->n_philo);
	free(vars);
}
