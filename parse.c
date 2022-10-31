#include "parse.h"

static void	print_token(t_token token)
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
}

static int	get_int(t_token token, t_params *params)
{
	int		n;
	char	*s;

	s = ft_strndup(token.start, token.len);
	if (s == NULL)
	{
		perror("malloc");
		clean_exit(EXIT_FAILURE, params);
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
		clean_exit(EXIT_FAILURE, params);
	}
	n = ft_atof(s);
	free(s);
	return (n);
}

static t_token	match(int type, t_parse_utils *utils, t_params *params)
{
	t_token	prev;

	if (utils->token.type == ERROR_TOKEN)
	{
		printf("Error\n");
		printf("line %d: '%.*s' is not a valid token\n", \
		utils->line, utils->token.len, utils->token.start);
		clean_exit(EXIT_FAILURE, params);
	}
	else if ((type & utils->token.type) == 0)
	{
		printf("Error\n");
		printf("line %d: unexpected token '%.*s'\n", \
		utils->line, utils->token.len, utils->token.start);
		clean_exit(EXIT_FAILURE, params);
	}
	prev = utils->token;
	print_token(utils->token);
	utils->token = scan_token(&utils->scanner);
	return (prev);
}

static void	get_ambient_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->ambient != NULL)
	{
		printf("Error\n");
		printf("line %d: ambient lightning set twice\n", utils->line);
		clean_exit(EXIT_FAILURE, params);
	}
	params->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (params->ambient == NULL)
	{
		perror("malloc");
		clean_exit(EXIT_FAILURE, params);
	}
	prev = match(INT_TOKEN | FLOAT_TOKEN, utils, params);
	params->ambient->ambient_ratio = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	params->ambient->rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	params->ambient->rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	params->ambient->rgb.blue = get_int(prev, params);
}

static void	get_camera(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->camera != NULL)
	{
		printf("Error\n");
		printf("line %d: camera set twice\n", utils->line);
		clean_exit(EXIT_FAILURE, params);
	}
	params->camera = (t_camera *)malloc(sizeof(t_camera));
	if (params->camera == NULL)
	{
		perror("malloc");
		clean_exit(EXIT_FAILURE, params);
	}
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->camera->orient.z = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	params->camera->fov = get_int(prev, params);
}

static void	get_light(t_params *params, t_parse_utils *utils)
{
	t_token	prev;

	if (params->light != NULL)
	{
		printf("Error\n");
		printf("line %d\n: light set twice\n", utils->line);
		clean_exit(EXIT_FAILURE, params);
	}
	params->light = (t_light *)malloc(sizeof(t_light));
	if (params->light == NULL)
	{
		perror("malloc");
		clean_exit(EXIT_FAILURE, params);
	}
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->light->coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->light->coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->light->coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	params->light->bright_ratio = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	params->light->rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	params->light->rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
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
		clean_exit(EXIT_FAILURE, params);
	}
	obj->type = SPHERE;
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->sphere.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->sphere.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->sphere.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->sphere.diameter = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	obj->sphere.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	obj->sphere.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
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
		clean_exit(EXIT_FAILURE, params);
	}
	obj->type = PLANE;
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->plane.orient.z = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	obj->plane.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	obj->plane.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
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
		clean_exit(EXIT_FAILURE, params);
	}
	obj->type = CYLINDER;
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.coord.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.coord.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.coord.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.orient.x = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.orient.y = get_float(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.orient.z = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.diameter = get_float(prev, params);
	prev = match(FLOAT_TOKEN | INT_TOKEN, utils, params);
	obj->cylinder.height = get_float(prev, params);
	prev = match(INT_TOKEN, utils, params);
	obj->cylinder.rgb.red = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	obj->cylinder.rgb.green = get_int(prev, params);
	match(COMMA_TOKEN, utils, params);
	prev = match(INT_TOKEN, utils, params);
	obj->cylinder.rgb.blue = get_int(prev, params);
	obj->next = NULL;
	params->obj_set = append_obj_set(params->obj_set, obj);
}

static void	get_object(t_params *params, t_parse_utils *utils)
{
	if (utils->token.type == AMBIENT_TOKEN)
	{
		match(AMBIENT_TOKEN, utils, params);
		get_ambient_light(params, utils);
	}
	else if (utils->token.type == CAMERA_TOKEN)
	{
		match(CAMERA_TOKEN, utils, params);
		get_camera(params, utils);
	}
	else if (utils->token.type == LIGHT_TOKEN)
	{
		match(LIGHT_TOKEN, utils, params);
		get_light(params, utils);
	}
	else if (utils->token.type == SPHERE_TOKEN)
	{
		match(SPHERE_TOKEN, utils, params);
		get_sphere(params, utils);
	}
	else if (utils->token.type == PLANE_TOKEN)
	{
		match(PLANE_TOKEN, utils, params);
		get_plane(params, utils);
	}
	else if (utils->token.type == CYLINDER_TOKEN)
	{
		match(CYLINDER_TOKEN, utils, params);
		get_cylinder(params, utils);
	}
	else if (utils->token.type == NEWLINE_TOKEN)
	{
		match(NEWLINE_TOKEN, utils, params);
		utils->line++;
		get_object(params, utils);
	}
	else
		match(ERROR_TOKEN, utils, params);
	if (utils->token.type != EOF_TOKEN)
	{
		printf("\n");
		get_object(params, utils);
	}
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

void	check_params(t_params params)
{
	int	error;

	error = 0;
	if (params.light == NULL)
		error |= MISSING_LIGHT;
	else if (params.ambient == NULL)
		error |= MISSING_AMBIENT;
	else if (params.camera == NULL)
		error |= MISSING_CAM;
	if (error != 0)
	{
		printf("Error\n");
		print_param_error(error);
		clean_exit(EXIT_FAILURE, &params);
	}
}

t_params	parse(char *s)
{
	t_params		params;
	t_parse_utils	utils;

	bzero(&params, sizeof(params));
	params.file_contents = s;
	utils.line = 1;
	init_scanner(&utils.scanner, s);
	utils.token = scan_token(&utils.scanner);
	get_object(&params, &utils);
	check_params(params);
	return (params);
}
