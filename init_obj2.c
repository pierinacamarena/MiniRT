/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:15:48 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 12:47:49 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	is_already_set(int which, t_params *params, t_parse_utils *utils)
{
	if (utils->panic == 1)
		return ;
	if ((which & AMBIENT_TOKEN) != 0 && params->ambient != NULL)
	{
		printf("Error\n");
		printf("line %d: ambient lighting set twice\n", utils->line);
		utils->panic = 1;
	}
	else if ((which & CAMERA_TOKEN) != 0 && params->camera != NULL)
	{
		printf("Error\n");
		printf("line %d: camera set twice\n", utils->line);
		utils->panic = 1;
	}
	else if ((which & LIGHT_TOKEN) != 0 && params->light != NULL)
	{
		printf("Error\n");
		printf("line %d: point light set twice\n", utils->line);
		utils->panic = 1;
	}
}

void	get_ambient_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	is_already_set(AMBIENT_TOKEN, params, utils);
	if (utils->panic == 1)
		return ;
	params->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (params->ambient == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	prev = match(INT_TOKEN | FLOAT_TOKEN, utils);
	params->ambient->ambient_ratio = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	params->ambient->rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	params->ambient->rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	params->ambient->rgb.blue = get_int(prev, params);
}

void	get_camera(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	is_already_set(CAMERA_TOKEN, params, utils);
	if (utils->panic == 1)
		return ;
	params->camera = (t_camera *)malloc(sizeof(t_camera));
	if (params->camera == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	get_cam_coord(params, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->orient.z = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	params->camera->fov = get_int(prev, params);
}

void	get_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	is_already_set(LIGHT_TOKEN, params, utils);
	if (utils->panic == 1)
		return ;
	params->light = (t_light *)malloc(sizeof(t_light));
	if (params->light == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	get_light_coord(params, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->bright_ratio = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	params->light->rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	params->light->rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	params->light->rgb.blue = get_int(prev, params);
}
