#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdlib.h>

double	min(double a, double b);
double	max(double a, double b);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(char *s);
double	ft_atof(char *s);
char	*ft_strndup(const char *s, size_t n);

#endif
