/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:17:44 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 18:02:11 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
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
		n = n * 10.0 + (double)((*s++ - '0') * sign);
	if (*s == '.')
		s++;
	pow = 1.0;
	while (ft_isdigit(*s))
	{
		n = n * 10.0 + (double)((*s++ - '0') * sign);
		pow *= 10.0;
	}
	return (n / pow);
}
