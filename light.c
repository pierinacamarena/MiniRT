/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:13:45 by pcamaren          #+#    #+#             */
/*   Updated: 2022/11/09 15:04:01 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_color.h"

double	calc_specular(t_params params, t_vector dir_light, \
t_vector n_hit, t_vector p_hit)
{
	t_vector	cam_view;
	t_vector	add;
	t_vector	h;
	double		r2;

	r2 = vec_dot(dir_light, dir_light);
	dir_light = unit_vec(dir_light);
	cam_view = vec_diff(params.camera->coord, p_hit);
	cam_view = unit_vec(cam_view);
	add = vec_add(cam_view, dir_light);
	h = vec_scale(add, 1 / vec_length(add));
	return (POWER * pow(max(0.0, vec_dot(n_hit, h)), SHININESS) / r2);
}

double	light_dot_normal(t_light light, t_vector p_hit, \
t_vector n_hit, t_params params)
{
	t_vector	dir_light;
	double		specular;
	double		r2;

	specular = 0.0;
	dir_light = vec_diff(light.coord, p_hit);
	r2 = vec_dot(dir_light, dir_light);
	specular = calc_specular(params, dir_light, n_hit, p_hit);
	dir_light = unit_vec(dir_light);
	return ((POWER / r2 * max(0.0, vec_dot(dir_light, n_hit)) + specular));
}

int	is_in_shadow(t_vector p_hit, t_vector n_hit, t_params params)
{
	t_vector	dir_light;
	t_obj		obj;
	double		t;
	double		dist;
	double		shadow_bias;

	shadow_bias = 1E-4;
	dir_light = unit_vec(vec_diff(params.light->coord, p_hit));
	p_hit = vec_add(p_hit, vec_scale(n_hit, shadow_bias));
	dist = vec_length(vec_diff(params.light->coord, p_hit));
	t = hit_object(ray_create(p_hit, dir_light), params.obj_set, &obj);
	if (t > 0.0 && t < dist)
		return (1);
	return (0);
}
