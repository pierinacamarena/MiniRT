/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:23:55 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 12:23:57 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_params.h"

static int	check_camera(t_camera *camera)
{
	int	error;

	error = 0;
	if (camera == NULL)
		return (MISSING_CAM);
	error |= check_coord_limit(camera->coord);
	error |= check_orient_limit(camera->orient);
	error |= check_fov_limit(camera->fov);
	return (error);
}

static int	check_ambient(t_ambient *ambient)
{
	int	error;

	error = 0;
	if (ambient == NULL)
		return (MISSING_AMBIENT);
	error |= check_light_ratio_limit(ambient->ambient_ratio);
	error |= check_rgb_limit(ambient->rgb);
	return (error);
}

static int	check_light(t_light *light)
{
	int	error;

	error = 0;
	if (light == NULL)
		return (MISSING_LIGHT);
	error |= check_coord_limit(light->coord);
	error |= check_light_ratio_limit(light->bright_ratio);
	error |= check_rgb_limit(light->rgb);
	return (error);
}

int	check_params(t_params *params)
{
	int	error;

	error = 0;
	error |= check_camera(params->camera);
	error |= check_ambient(params->ambient);
	error |= check_light(params->light);
	error |= check_obj_set(params->obj_set);
	return (error);
}
