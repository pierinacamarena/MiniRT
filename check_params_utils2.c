/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:25:11 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 12:25:13 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_params.h"

static int	check_sphere(t_sphere sphere)
{
	int	error;

	error = 0;
	error |= check_coord_limit(sphere.coord);
	if (sphere.diameter <= 0 || sphere.diameter > U_LIMIT)
		error |= DIAMETER_LIMIT;
	error |= check_rgb_limit(sphere.rgb);
	return (error);
}

static int	check_cylinder(t_cylinder cylinder)
{
	int	error;

	error = 0;
	error |= check_coord_limit(cylinder.coord);
	error |= check_orient_limit(cylinder.orient);
	if (cylinder.diameter <= 0 || cylinder.diameter > U_LIMIT)
		error |= DIAMETER_LIMIT;
	if (cylinder.height <= 0 || cylinder.height > U_LIMIT)
		error |= HEIGHT_LIMIT;
	error |= check_rgb_limit(cylinder.rgb);
	return (error);
}

static int	check_plane(t_plane plane)
{
	int	error;

	error = 0;
	error |= check_coord_limit(plane.coord);
	error |= check_orient_limit(plane.orient);
	error |= check_rgb_limit(plane.rgb);
	return (error);
}

int	check_obj_set(t_obj *obj_set)
{
	int	error;

	error = 0;
	while (obj_set != NULL)
	{
		if (obj_set->type == SPHERE)
			error |= check_sphere(obj_set->sphere);
		else if (obj_set->type == CYLINDER)
			error |= check_cylinder(obj_set->cylinder);
		else if (obj_set->type == PLANE)
			error |= check_plane(obj_set->plane);
		obj_set = obj_set->next;
	}
	return (error);
}
