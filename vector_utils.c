/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:26:55 by pcamaren          #+#    #+#             */
/*   Updated: 2022/11/11 14:47:54 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

inline double	vec_dot(t_vector v, t_vector w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

inline double	vec_length(t_vector v)
{
	double	squared_length;

	squared_length = pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0);
	return (sqrt(squared_length));
}

inline t_vector	unit_vec(t_vector v)
{
	return (vec_scale(v, 1.0 / vec_length(v)));
}

inline void	vec_print(t_vector v)
{
	printf("[[ %f ]\n [ %f ]\n [ %f ]]\n", v.x, v.y, v.z);
}

inline int	is_zero(t_vector v)
{
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		return (1);
	return (0);
}
