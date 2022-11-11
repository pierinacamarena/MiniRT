/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:48:27 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 14:52:04 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_image.h"

static double	degree_to_radian(int degrees)
{
	return ((double)degrees / 360.0 * 2.0 * PI);
}

static t_vector	get_dir(double u, double v, t_camera camera)
{
	t_vector	right;
	t_vector	up;
	t_vector	temp;
	t_vector	dir;

	temp = vec_create(0, 1, 0);
	right = vec_cross(camera.orient, temp);
	up = vec_cross(right, camera.orient);
	if (vec_dot(right,right) == 0.0)
	{
		temp = vec_create(0, 0, 1);
		right = vec_cross(camera.orient, temp);
		up = vec_cross(camera.orient, right);
	}
	up = unit_vec(up);
	right = unit_vec(right);
	dir = vec_scale(right, u);
	dir = vec_add(vec_scale(up, v), dir);
	dir = vec_add(vec_scale(unit_vec(camera.orient), FOCAL_LEN), dir);
	return (unit_vec(dir));
}

static void	color_pixel(t_params *params, t_img *img, int x, int y)
{
	t_ray	ray;
	double	u;
	double	v;
	double	height;

	height = WIDTH / RATIO;
	u = ((double)x / (WIDTH - 1.0) - 0.5) * params->view_width;
	v = ((double)y / (height - 1.0) - 0.5) * params->view_height;
	ray = ray_create(params->camera->coord, get_dir(u, v, *params->camera));
	put_pixel(img, x, height - y - 1, ray_color(ray, *params));
}

void	color_image(t_params *params, t_img *img)
{
	double	theta;
	int		x;
	int		y;
	double	height;

	height = WIDTH / RATIO;
	theta = degree_to_radian(params->camera->fov);
	params->view_width = 2.0 * tan(theta / 2.0) * FOCAL_LEN;
	params->view_height = params->view_width / RATIO;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < height)
		{
			color_pixel(params, img, x, y);
			y++;
		}
		x++;
	}
}

t_img	*replace_image(t_img *old_img, t_data *data)
{
	t_img	*new_img;

	new_img = get_new_image(data->mlx);
	if (new_img == NULL)
		return (NULL);
	color_image(data->params, new_img);
	mlx_destroy_image(data->mlx->mlx, old_img->img);
	free(old_img);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, \
new_img->img, 0, 0);
	return (new_img);
}
