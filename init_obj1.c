/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:39:37 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 12:36:16 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	get_sphere(t_params *params, t_parse_utils *utils)
{
	t_obj	*obj;
	t_token	prev;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	obj->type = SPHERE;
	get_coord(obj, params, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->sphere.diameter = get_float(prev, params);
	get_surf_rgb(obj, params, utils);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

void	get_plane(t_params *params, t_parse_utils *utils)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	obj->type = PLANE;
	get_coord(obj, params, utils);
	get_orient(obj, params, utils);
	get_surf_rgb(obj, params, utils);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

void	get_cylinder(t_params *params, t_parse_utils *utils)
{
	t_obj	*obj;
	t_token	prev;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	obj->type = CYLINDER;
	get_coord(obj, params, utils);
	get_orient(obj, params, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.diameter = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.height = get_float(prev, params);
	get_surf_rgb(obj, params, utils);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}
