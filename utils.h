/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:57:49 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:57:54 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdlib.h>

double	min(double a, double b);
double	max(double a, double b);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_atoi(char *s);
double	ft_atof(char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);

#endif
