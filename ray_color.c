#include "ray_color.h"

t_vector	color_to_vec(t_color color)
{
	t_vector	vec;

	vec.x = (double)color.red;
	vec.y = (double)color.green;
	vec.z = (double)color.blue;
	return (vec);
}

t_color	vec_to_color(t_vector vec)
{
	t_color	color;

	color.red = (int)min(255.0, max(0.0, vec.x));
	color.green = (int)min(255.0, max(0.0, vec.y));
	color.blue = (int)min(255.0, max(0.0, vec.z));
	return (color);
}

double	light_dot_normal(t_light light, t_vector p_hit, t_vector n_hit)
{
	t_vector	dir_light;

	dir_light = unit_vec(vec_diff(light.coord, p_hit));
	return (max(0.0, vec_dot(dir_light, n_hit)));
}

int	get_color(t_obj obj, t_ambient ambient, t_light light, double l_dot_n)
{
	t_color	base_rgb;
	double	red;
	double	green;
	double	blue;

	if (obj.type == SPHERE)
		base_rgb = obj.sphere.rgb;
	else if (obj.type == PLANE)
		base_rgb = obj.plane.rgb;
	else if (obj.type == CYLINDER)
		base_rgb = obj.cylinder.rgb;
	red = (double)base_rgb.red * (ambient.ambient_ratio * (double)ambient.rgb.red / 255.0 + light.bright_ratio * l_dot_n * (double)light.rgb.red / 255.0);
	green = (double)base_rgb.green * (ambient.ambient_ratio * (double)ambient.rgb.green / 255.0 + light.bright_ratio * l_dot_n * (double)light.rgb.green / 255.0);
	blue = (double)base_rgb.blue * (ambient.ambient_ratio * (double)ambient.rgb.blue / 255.0 + light.bright_ratio * l_dot_n * (double)light.rgb.blue / 255.0);
	red = min(255.0, max(0.0, red));
	green = min(255.0, max(0.0, green));
	blue = min(255.0, max(0.0, blue));
	return (create_color((int)red, (int)green, (int)blue));
}

static t_vector	get_normal(t_vector p_hit, t_vector from, t_obj obj)
{
	double		z;
	t_vector	n_hit;

	if (obj.type == SPHERE)
		n_hit = unit_vec(vec_diff(p_hit, obj.sphere.coord));
	else if (obj.type == PLANE)
		n_hit = unit_vec(obj.plane.orient);
	else if (obj.type == CYLINDER)
	{
		z = vec_dot(unit_vec(obj.cylinder.orient), vec_diff(p_hit, obj.cylinder.coord));
		n_hit = unit_vec(vec_diff(p_hit, vec_add(obj.cylinder.coord, vec_scale(unit_vec(obj.cylinder.orient), z))));
	}
	if (vec_dot(n_hit, unit_vec(vec_diff(p_hit, from))) > 0.0)
		n_hit = vec_scale(n_hit, -1.0);
	return (n_hit);
}

static int	is_in_shadow(t_vector p_hit, t_vector n_hit, t_params params)
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

int	ray_color(t_ray ray, t_params params)
{
	t_obj		obj;
	double		t;
	t_vector	p_hit;
	t_vector	n_hit;
	double		l_dot_n;

	t = hit_object(ray, params.obj_set, &obj);
	p_hit = ray_at(ray, t);
	n_hit = get_normal(p_hit, params.camera->coord, obj);
	if (t < T_MAX)
	{
		l_dot_n = 0.0;
		if (!is_in_shadow(p_hit, n_hit, params))
			l_dot_n = light_dot_normal(*params.light, p_hit, n_hit);
		return (get_color(obj, *params.ambient, *params.light, l_dot_n));
	}
	return (0);
}
