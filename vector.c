/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:26:23 by pcamaren          #+#    #+#             */
/*   Updated: 2022/11/11 14:47:49 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec_create(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

inline t_vector	vec_add(t_vector v, t_vector w)
{
	t_vector	ret;

	ret.x = v.x + w.x;
	ret.y = v.y + w.y;
	ret.z = v.z + w.z;
	return (ret);
}

inline t_vector	vec_diff(t_vector v, t_vector w)
{
	t_vector	ret;

	ret.x = v.x - w.x;
	ret.y = v.y - w.y;
	ret.z = v.z - w.z;
	return (ret);
}

inline t_vector	vec_scale(t_vector v, double t)
{
	t_vector	ret;

	ret.x = v.x * t;
	ret.y = v.y * t;
	ret.z = v.z * t;
	return (ret);
}

inline t_vector	vec_cross(t_vector v, t_vector w)
{
	double	x;
	double	y;
	double	z;

	x = v.y * w.z - v.z * w.y;
	y = v.z * w.x - v.x * w.z;
	z = v.x * w.y - v.y * w.x;
	return (vec_create(x, y, z));
}

// inline double	vec_dot(t_vector v, t_vector w)
// {
// 	return (v.x * w.x + v.y * w.y + v.z * w.z);
// }

// inline double	vec_length(t_vector v)
// {
// 	double	squared_length;

// 	squared_length = pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0);
// 	return (sqrt(squared_length));
// }

// inline t_vector	unit_vec(t_vector v)
// {
// 	return (vec_scale(v, 1.0 / vec_length(v)));
// }

// inline void	vec_print(t_vector v)
// {
// 	printf("[[ %f ]\n [ %f ]\n [ %f ]]\n", v.x, v.y, v.z);
// }
