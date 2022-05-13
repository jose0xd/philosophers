#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	tp;
	struct timezone	tzp;

	gettimeofday(&tp, &tzp);
	printf("tv_sec: %ld\ntv_usec: %d\ntz_minuteswest: %d\ntz_dsttime: %d\n",
			tp.tv_sec, tp.tv_usec, tzp.tz_minuteswest, tzp.tz_dsttime);
	printf("miliseconds: %ld\n", tp.tv_sec * 1000 + (long)tp.tv_usec / 1000);
}
