/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:53:23 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/07 23:06:27 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

static double	hit_sphere(t_ray ray, t_sphere sphere)
{
	t_vars		var;

	var.oc = vec_diff(ray.orig, sphere.coord);
	var.a = vec_dot(ray.dir, ray.dir);
	var.b = 2.0 * vec_dot(var.oc, ray.dir);
	var.c = vec_dot(var.oc, var.oc) - pow(sphere.diameter / 2.0, 2.0);
	var.discr = pow(var.b, 2.0) - 4.0 * var.a * var.c;
	if (var.discr < 0.0)
		return (-1);
	var.t = (var.b * -1.0 - sqrt(var.discr)) / (2.0 * var.a);
	if (var.t < 0.0)
		var.t = (var.b * -1.0 + sqrt(var.discr)) / (2.0 * var.a);
	return (var.t);
}

static double	hit_plane(t_ray ray, t_plane plane)
{
	double		t;

	if (vec_dot(plane.orient, ray.dir) != 0)
	{
		t = vec_dot(plane.orient, vec_diff(plane.coord, ray.orig));
		t /= vec_dot(plane.orient, ray.dir);
	}
	else
		t = T_MAX;
	return (t);
}

static double	hit_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vars		var;

	set_vectors(ray, cylinder, &var);
	set_doubles(ray, cylinder, &var);
	if (var.discr < 0.0)
		return (-1.0);
	var.t = (-1.0 * var.b - sqrt(var.discr)) / (2.0 * var.a);
	var.intersect = ray_at(ray, var.t);
	var.z = vec_dot(unit_vec(cylinder.orient), \
	vec_diff(var.intersect, cylinder.coord));
	if ((var.z > 0.0 && var.z > cylinder.height / 2.0) \
	|| (var.z < 0.0 && var.z < -1.0 * cylinder.height / 2.0) || var.t < 0.0)
	{
		var.t = (-1.0 * var.b + sqrt(var.discr)) / (2.0 * var.a);
		var.intersect = ray_at(ray, var.t);
		var.z = vec_dot(unit_vec(cylinder.orient), \
		vec_diff(var.intersect, cylinder.coord));
		if ((var.z > 0.0 && var.z > cylinder.height / 2.0) \
		|| (var.z < 0.0 && var.z < -1.0 * cylinder.height / 2.0))
			return (-1.0);
	}
	return (var.t);
}

double	hit_object(t_ray ray, t_obj *obj_set, t_obj *obj)
{
	double	t;
	double	temp;

	t = T_MAX;
	while (obj_set != NULL)
	{
		if (obj_set->type == SPHERE)
			temp = hit_sphere(ray, obj_set->sphere);
		else if (obj_set->type == PLANE)
			temp = hit_plane(ray, obj_set->plane);
		else if (obj_set->type == CYLINDER)
			temp = hit_cylinder(ray, obj_set->cylinder);
		if (temp > 0.0 && temp < t)
		{
			*obj = *obj_set;
			t = temp;
		}
		obj_set = obj_set->next;
	}
	return (t);
}
