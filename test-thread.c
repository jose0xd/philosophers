#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// mutex
// https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4
void	*f(void *args)
{
	int	data;

	data = *(int *)args;
	while (data > 0)
	{
		sleep(1);
		printf("data: %d\n", data);
		data--;
	}
	puts("Finish thread");
	return args;
	/*pthread_exit(args);*/
}

int	main(int ac, char **av)
{
	pthread_t	thread;
	pthread_t	thread2;
	int			numb;
	int			numb2;
	int			*data;

	if (ac != 2)
	{
		puts("Introduce a number");
		return (0);
	}
	numb = atoi(av[1]);
	if (pthread_create(&thread, NULL, f, &numb))
	{
		puts("Cannot open thread");
		return (-1);
	}
	numb2 = numb + 10;
	if (pthread_create(&thread2, NULL, f, &numb2))
	{
		puts("Cannot open thread");
		return (-1);
	}
	/*pthread_detach(thread2);*/
	pthread_join(thread2, (void **)&data);
	printf("Main finish... data: %d\n", *data);
	/*pthread_exit(0);*/
	exit(0);
}
