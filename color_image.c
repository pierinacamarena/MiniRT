#include "color_image.h"

static double	degree_to_radian(int degrees)
{
	return ((double)degrees / 360.0 * 2.0 * PI);
}

static t_vector	get_dir(double u, double v, t_camera camera) { t_vector	right; t_vector	up; t_vector	temp; t_vector	dir;
	temp = vec_create(0, 1, 0);
	right = vec_cross(camera.orient, temp);
	if (vec_dot(camera.orient, right) != 0)
	{
		temp = vec_create(0, 0, 1);
		right = vec_cross(camera.orient, temp);
	}
	up = vec_cross(right, camera.orient);
	dir = vec_scale(right, u);
	dir = vec_add(vec_scale(up, v), dir);
	dir = vec_add(vec_scale(camera.orient, FOCAL_LEN), dir);
	return (unit_vec(dir));
}

static void	color_pixel(t_params *params, t_img *img, int x, int y)
{
	t_ray	ray;
	double	u;
	double	v;

	u = ((double)x / (WIDTH - 1.0) - 0.5) * params->view_width;
	v = ((double)y / (HEIGHT - 1.0) - 0.5) * params->view_height;
	ray = ray_create(params->camera->coord, get_dir(u, v, *params->camera));
	put_pixel(img, x, HEIGHT - y - 1, ray_color(ray, *params));
}

void	color_image(t_params *params, t_img *img)
{
	double	theta;
	int		x;
	int		y;

	theta = degree_to_radian(params->camera->fov);
	params->view_width = 2.0 * tan(theta / 2.0) * FOCAL_LEN;
	params->view_height = params->view_width / RATIO;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color_pixel(params, img, x, y);
			y++;
		}
		x++;
	}
}
