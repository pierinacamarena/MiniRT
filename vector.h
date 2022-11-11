/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:58:15 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 14:41:26 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_vector_set {
	t_vector	origin;
	t_vector	horizon;
	t_vector	vertical;
	t_vector	bottom_left;
}	t_vector_set;

t_vector		vec_create(double x, double y, double z);
t_vector		vec_add(t_vector v, t_vector w);
t_vector		vec_diff(t_vector v, t_vector w);
t_vector		vec_scale(t_vector v, double t);
t_vector		vec_cross(t_vector v, t_vector w);
double			vec_dot(t_vector v, t_vector w);
double			vec_length(t_vector v);
t_vector		unit_vec(t_vector v);
int				is_zero(t_vector v);

void			vec_print(t_vector v);

#endif
