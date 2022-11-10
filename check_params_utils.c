#include "check_params.h"

int	check_coord_limit(t_vector coord)
{
	if (coord.x < L_LIMIT || coord.x > U_LIMIT)
		return (COORD_LIMIT);
	else if (coord.y < L_LIMIT || coord.y > U_LIMIT)
		return (COORD_LIMIT);
	else if (coord.z < L_LIMIT || coord.z > U_LIMIT)
		return (COORD_LIMIT);
	return (0);
}

int	check_orient_limit(t_vector orient)
{
	if (orient.x < -1.0 || orient.x > 1.0)
		return (ORIENT_LIMIT);
	else if (orient.y < -1.0 || orient.y > 1.0)
		return (ORIENT_LIMIT);
	else if (orient.z < -1.0 || orient.z > 1.0)
		return (ORIENT_LIMIT);
	return (0);
}

int	check_light_ratio_limit(double light_ratio)
{
	if (light_ratio < 0.0 || light_ratio > 1.0)
		return (LIGHT_RATIO_LIMIT);
	return (0);
}

int	check_fov_limit(int fov)
{
	if (fov <= 0 || fov >= 180)
		return (FOV_LIMIT);
	return (0);
}

int	check_rgb_limit(t_color rgb)
{
	if (rgb.red < 0 || rgb.red > 255)
		return (RGB_LIMIT);
	else if (rgb.green < 0 || rgb.green > 255)
		return (RGB_LIMIT);
	else if (rgb.blue < 0 || rgb.blue > 255)
		return (RGB_LIMIT);
	return (0);
}
