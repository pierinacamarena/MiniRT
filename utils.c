#include "utils.h"

double			max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double			min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *s)
{
	int	n;
	int	sign;

	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	n = 0;
	while (ft_isdigit(*s))
		n = n * 10 + (*s++ - '0') * sign;
	return (n);
}

double	ft_atof(char *s)
{
	double	n;
	double	dec;
	double	pow;
	double	sign;

	sign = 1.0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	n = 0.0;
	while (ft_isdigit(*s))
		n = n * 10.0 + (double)(*s++ - '0') * sign;
	if (*s == '.')
		s++;
	dec = 0.0;
	pow = 10.0;
	while (ft_isdigit(*s))
	{
		dec = dec + (double)(*s++ - '0') * sign / pow;
		pow *= 10.0;
	}
	return (n + dec);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	i;

	ret = malloc(n + 1);
	i = 0;
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
