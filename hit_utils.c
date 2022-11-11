/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:04:01 by pcamaren          #+#    #+#             */
/*   Updated: 2022/11/11 14:43:00 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	set_vectors(t_ray ray, t_cylinder cylinder, t_vars *var)
{
	var->vup = vec_create(0, 1, 0);
	var->right = vec_cross(unit_vec(cylinder.orient), var->vup);
	var->up = vec_cross(var->right, unit_vec(cylinder.orient));
	if (is_zero(var->right))
	{
		var->right = vec_cross(unit_vec(cylinder.orient), \
		vec_create(1, 0, 0));
		var->up = vec_cross(unit_vec(cylinder.orient), var->right);
	}
	var->right = unit_vec(var->right);
	var->up = unit_vec(var->up);
	var->oc = vec_diff(ray.orig, cylinder.coord);
}

void	set_doubles(t_ray ray, t_cylinder cylinder, t_vars *var)
{
	var->a = pow(vec_dot(ray.dir, var->up), 2) \
	+ pow(vec_dot(ray.dir, var->right), 2);
	var->b = 2 * (vec_dot(var->right, var->oc) * vec_dot(var->right, ray.dir) \
	+ vec_dot(var->up, var->oc) * vec_dot(var->up, ray.dir));
	var->c = pow(vec_dot(var->right, var->oc), 2.0) + \
	pow(vec_dot(var->up, var->oc), 2.0) \
	- pow((cylinder.diameter / 2.0), 2);
	var->discr = pow(var->b, 2.0) - 4.0 * var->a * var->c;
}
