#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>

#include "screen.h"
#include "color.h"
#include "vector.h"
#include "params.h"
#include "parse.h"
#include "ray.h"
#include "ray_color.h"

#define BUFSIZE 4096

static double	degree_to_radian(int degrees)
{
	return ((double)degrees / 360.0 * 2.0 * PI);
}

static char	*read_file(const char *filename)
{
	char	buf[BUFSIZE];
	int		fd;
	int		count;
	char	*file_contents;
	int		file_size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	file_size = 0;
	file_contents = NULL;
	count = read(fd, buf, BUFSIZE);
	while (count > 0)
	{
		if (count == -1)
		{
			perror("read");
			free(file_contents);
			close(fd);
			exit(EXIT_FAILURE);
		}
		file_contents = realloc(file_contents, file_size + count + 1);
		if (file_contents == NULL)
		{
			perror("realloc");
			close(fd);
			exit(EXIT_FAILURE);
		}
		file_contents[file_size] = '\0';
		strncat(file_contents, buf, count);
		file_size += count;
		count = read(fd, buf, BUFSIZE);
	}
	close(fd);
	return (file_contents);
}

static t_vector	get_dir(double u, double v, t_camera camera)
{
	t_vector	right;
	t_vector	up;
	t_vector	temp;
	t_vector	dir;

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

int	close_mlx(t_data *data)
{
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_params(data->params);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_window(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_mlx(data);
	return (0);
}

static void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGTH, "mini_rt");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits, &data->line, &data->endian);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_params	params;
	t_ray		ray;
	char		*file_contents;
	double		u;
	double		v;
	double		view_width;
	double		view_height;
	double		theta;

	if (argc != 2)
	{
		printf("invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	file_contents = read_file(argv[1]);
	if (file_contents == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	params = parse(file_contents);
	data.params = &params;
	free(file_contents);
	init_data(&data);
	theta = degree_to_radian(params.camera->fov);
	view_width = 2.0 * tan(theta / 2.0) * FOCAL_LEN;
	view_height = view_width / RATIO;	
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGTH; j++)
		{
			u = ((double)i / (WIDTH - 1.0) - 0.5) * view_width;
			v = ((double)j / (HEIGTH - 1.0) - 0.5) * view_height;
			ray = ray_create(params.camera->coord, get_dir(u, v, *params.camera));
			put_pixel(&data, i, HEIGTH - j - 1, ray_color(ray, params));
		}
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L<<0, close_window, &data);
	mlx_hook(data.mlx_win, 17, 1L<<1, close_mlx, &data);
	mlx_loop(data.mlx);
	return (0);
}
