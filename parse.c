#include "parse.h"

/*static void	print_token(t_token token)
{
	if (token.type == AMBIENT_TOKEN)
		printf("AMBIENT_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == CAMERA_TOKEN)
		printf("CAMERA_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == LIGHT_TOKEN)
		printf("LIGHT_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == SPHERE_TOKEN)
		printf("SPHERE_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == PLANE_TOKEN)
		printf("PLANE_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == CYLINDER_TOKEN)
		printf("CYLINDER_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == FLOAT_TOKEN)
		printf("FLOAT_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == INT_TOKEN)
		printf("INT_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == COMMA_TOKEN)
		printf("COMMA_TOKEN\t'%.*s'\n", token.len, token.start);
	else if (token.type == ERROR_TOKEN)
		printf("ERROR_TOKEN\t'%.*s'\n", token.len, token.start);
}*/

static int	get_int(t_token token, t_params *params)
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

static double	get_float(t_token token, t_params *params)
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

static t_token	match(int type, t_parse_utils *utils)
{
	t_token	prev;

	if (utils->token.type == ERROR_TOKEN && utils->panic == 0)
	{
		printf("Error\n");
		printf("line %d: '%.*s' is not a valid token\n", \
		utils->line, utils->token.len, utils->token.start);
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

static void	get_ambient_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->ambient != NULL && utils->panic == 0)
	{
		printf("Error\n");
		printf("line %d: ambient lightning set twice\n", utils->line);
		utils->panic = 1;
	}
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

static void	get_camera(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->camera != NULL && utils->panic == 0)
	{
		printf("Error\n");
		printf("line %d: camera set twice\n", utils->line);
		utils->panic = 1;
	}
	if (utils->panic == 1)
		return ;
	params->camera = (t_camera *)malloc(sizeof(t_camera));
	if (params->camera == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->camera->coord.z = get_float(prev, params);
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

static void	get_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->light != NULL && utils->panic == 0)
	{
		printf("Error\n");
		printf("line %d\n: light set twice\n", utils->line);
		utils->panic = 1;
	}
	if (utils->panic == 1)
		return ;
	params->light = (t_light *)malloc(sizeof(t_light));
	if (params->light == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	params->light->coord.z = get_float(prev, params);
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

static void	get_sphere(t_params *params, t_parse_utils *utils)
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
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->sphere.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->sphere.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->sphere.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->sphere.diameter = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	obj->sphere.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->sphere.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->sphere.rgb.blue = get_int(prev, params);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

static void	get_plane(t_params *params, t_parse_utils *utils)
{
	t_obj	*obj;
	t_token	prev;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		perror("malloc");
		clean_params_exit(EXIT_FAILURE, params);
	}
	obj->type = PLANE;
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->plane.orient.z = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	obj->plane.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->plane.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->plane.rgb.blue = get_int(prev, params);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

static void	get_cylinder(t_params *params, t_parse_utils *utils)
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
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.orient.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.diameter = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils);
	obj->cylinder.height = get_float(prev, params);
	prev = match(INT_TOKEN, utils);
	obj->cylinder.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->cylinder.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils);
	prev = match(INT_TOKEN, utils);
	obj->cylinder.rgb.blue = get_int(prev, params);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

static void	get_object(t_params *params, t_parse_utils *utils)
{
	if (utils->token.type == AMBIENT_TOKEN)
	{
		match(AMBIENT_TOKEN, utils);
		get_ambient_light(params, utils);
	}
	else if (utils->token.type == CAMERA_TOKEN)
	{
		match(CAMERA_TOKEN, utils);
		get_camera(params, utils);
	}
	else if (utils->token.type == LIGHT_TOKEN)
	{
		match(LIGHT_TOKEN, utils);
		get_light(params, utils);
	}
	else if (utils->token.type == SPHERE_TOKEN)
	{
		match(SPHERE_TOKEN, utils);
		get_sphere(params, utils);
	}
	else if (utils->token.type == PLANE_TOKEN)
	{
		match(PLANE_TOKEN, utils);
		get_plane(params, utils);
	}
	else if (utils->token.type == CYLINDER_TOKEN)
	{
		match(CYLINDER_TOKEN, utils);
		get_cylinder(params, utils);
	}
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

void	print_param_error(int error)
{
	if ((error & MISSING_LIGHT) != 0)
		printf("Point light missing.\n");
	else if ((error & MISSING_CAM) != 0)
		printf("Camera missing.\n");
	else if ((error & MISSING_AMBIENT) != 0)
		printf("Ambient light missing.\n");
}

void	check_params(t_params *params, t_parse_utils *utils)
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
	bzero(params, sizeof(t_params)); //make custom
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
