/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:52:05 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 13:10:34 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_int(t_token token, t_params *params)
{
	int		n;
	char	*s;

	s = ft_strndup(token.start, token.len);
	if (s == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	n = ft_atoi(s);
	free(s);
	return (n);
}

double	get_float(t_token token, t_params *params)
{
	double	n;
	char	*s;

	s = ft_strndup(token.start, token.len);
	if (s == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	n = ft_atof(s);
	free(s);
	return (n);
}

t_token	match(int type, t_parse_utils *utils)
{
	t_token	prev;

	if (utils->token.type == ERROR_TOKEN && utils->panic == 0)
	{
		print_token_error("is not a valid token", utils->line, utils->token);
		utils->panic = 1;
	}
	else if (utils->token.type == ERROR_LEN_TOKEN && utils->panic == 0)
	{
		print_token_error("is too long", utils->line, utils->token);
		utils->panic = 1;
	}
	else if ((type & utils->token.type) == 0 && utils->panic == 0)
	{
		printf("Error\n");
		if (utils->token.type == NEWLINE_TOKEN)
			printf("line %d: unexpected token 'newline'\n", utils->line);
		printf("line %d: unexpected token '%.*s'\n", \
		utils->line, utils->token.len, utils->token.start);
		utils->panic = 1;
	}
	prev = utils->token;
	utils->token = scan_token(&utils->scanner);
	return (prev);
}

static void	match_and_get_obj(int type, t_params *params, t_parse_utils *utils)
{
	match(type, utils);
	if (type == AMBIENT_TOKEN)
		get_ambient_light(params, utils);
	else if (type == CAMERA_TOKEN)
		get_camera(params, utils);
	else if (type == LIGHT_TOKEN)
		get_light(params, utils);
	else if (type == SPHERE_TOKEN)
		get_sphere(params, utils);
	else if (type == PLANE_TOKEN)
		get_plane(params, utils);
	else if (type == CYLINDER_TOKEN)
		get_cylinder(params, utils);
}

void	get_object(t_params *params, t_parse_utils *utils)
{
	if (utils->token.type == AMBIENT_TOKEN)
		match_and_get_obj(AMBIENT_TOKEN, params, utils);
	else if (utils->token.type == CAMERA_TOKEN)
		match_and_get_obj(CAMERA_TOKEN, params, utils);
	else if (utils->token.type == LIGHT_TOKEN)
		match_and_get_obj(LIGHT_TOKEN, params, utils);
	else if (utils->token.type == SPHERE_TOKEN)
		match_and_get_obj(SPHERE_TOKEN, params, utils);
	else if (utils->token.type == PLANE_TOKEN)
		match_and_get_obj(PLANE_TOKEN, params, utils);
	else if (utils->token.type == CYLINDER_TOKEN)
		match_and_get_obj(CYLINDER_TOKEN, params, utils);
	else if (utils->token.type == NEWLINE_TOKEN)
	{
		match(NEWLINE_TOKEN, utils);
		utils->line++;
		get_object(params, utils);
	}
	else
		match(ERROR_TOKEN, utils);
	if (utils->token.type != EOF_TOKEN)
		get_object(params, utils);
}
