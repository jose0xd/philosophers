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
