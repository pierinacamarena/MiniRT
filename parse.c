/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:21:13 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 11:36:18 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	print_param_error(int error)
{
	if ((error & MISSING_LIGHT) != 0)
		printf("Point light missing.\n");
	else if ((error & MISSING_CAM) != 0)
		printf("Camera missing.\n");
	else if ((error & MISSING_AMBIENT) != 0)
		printf("Ambient light missing.\n");
}

static void	check_params(t_params *params, t_parse_utils *utils)
{
	int	error;

	error = 0;
	if (params->light == NULL)
		error |= MISSING_LIGHT;
	else if (params->ambient == NULL)
		error |= MISSING_AMBIENT;
	else if (params->camera == NULL)
		error |= MISSING_CAM;
	if (error != 0)
	{
		printf("Error\n");
		print_param_error(error);
		utils->panic = 1;
	}
}

t_params	*parse(const char *s)
{
	t_params		*params;
	t_parse_utils	utils;

	params = (t_params *)malloc(sizeof(t_params));
	if (params == NULL)
		return (NULL);
	bzero(params, sizeof(t_params));
	utils.line = 1;
	init_scanner(&utils.scanner, s);
	utils.token = scan_token(&utils.scanner);
	utils.panic = 0;
	get_object(params, &utils);
	check_params(params, &utils);
	if (utils.panic == 1)
	{
		free_params(params);
		return (NULL);
	}
	return (params);
}
