/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:50:36 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 12:51:13 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	get_coord(t_obj *obj, t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.coord.x = get_float(prev, params);
	else if (obj->type == PLANE)
		obj->plane.coord.x = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.coord.y = get_float(prev, params);
	else if (obj->type == PLANE)
		obj->plane.coord.y = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.coord.z = get_float(prev, params);
	else if (obj->type == PLANE)
		obj->plane.coord.z = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.coord.z = get_float(prev, params);
}

void	get_cam_coord(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.z = get_float(prev, params);
}

void	get_light_coord(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.z = get_float(prev, params);
}

void	get_orient(t_obj *obj, t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == PLANE)
		obj->plane.orient.x = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == PLANE)
		obj->plane.orient.y = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	if (obj->type == PLANE)
		obj->plane.orient.z = get_float(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.orient.z = get_float(prev, params);
}

void	get_surf_rgb(t_obj *obj, t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	prev = match(INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.rgb.red = get_int(prev, params);
	else if (obj->type == PLANE)
		obj->plane.rgb.red = get_int(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.rgb.green = get_int(prev, params);
	else if (obj->type == PLANE)
		obj->plane.rgb.green = get_int(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.rgb.blue = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	if (obj->type == SPHERE)
		obj->sphere.rgb.blue = get_int(prev, params);
	else if (obj->type == PLANE)
		obj->plane.rgb.blue = get_int(prev, params);
	else if (obj->type == CYLINDER)
		obj->cylinder.rgb.blue = get_int(prev, params);
}
