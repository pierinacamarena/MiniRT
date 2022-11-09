#include "utils.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
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

char	*ft_strjoin(char *s1, const char *s2)
{	
	char	*res;
	char	*p;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
		return (NULL);
	p = res;
	while (s1 != NULL && *s1 != '\0')
		*p++ = *s1++;
	while (s2 != NULL && *s2 != '\0')
		*p++ = *s2++;
	*p = '\0';
	free(s1);
	return (res);
}

char	*ft_realloc(char *ptr, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(size);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < size && ptr != NULL && ptr[i] != '\0')
	{
		res[i] = ptr[i];
		i++;
	}
	res[i] = '\0';
	free(ptr);
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i++ < n)
		*ptr++ = '\0';
}
