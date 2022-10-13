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

#define BUFSIZE 4096

char	*read_file(const char *filename)
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

t_vector	get_dir(double u, double v, t_camera camera)
{
	double	x;
	double	y;
	double	z;

	x = u - camera.coord.x;
	y = v - camera.coord.y;
	z = camera.coord.z - FOCAL_LEN; //may have to change this
	return (vec_create(x, y, z));
}

double	hit_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discr;

	oc = vec_diff(ray.orig, sphere.coord);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0 * vec_dot(oc, ray.dir);
	c = vec_dot(oc , oc) - pow(sphere.diameter / 2.0, 2.0);
	discr = pow(b, 2.0) - 4.0 * a * c;
	if (discr < 0.0)
		return (-1);
	else
		return ((b * -1.0 - sqrt(discr)) / (2.0 * a));
}

double	hit_object(t_ray ray, t_obj *obj_set, t_obj *obj)
{
	double	t;
	double	temp;

	t = T_MAX;
	while (obj_set != NULL)
	{
		if (obj_set->type == SPHERE)
		{
			temp = hit_sphere(ray, obj_set->sphere);
			if (temp > 0.0 && temp < t)
			{
				*obj = *obj_set;
				t = temp;
			}
		}
		obj_set = obj_set->next;
	}
	return (t);
}
			
t_color	ray_color(t_ray ray, t_params params)
{
	t_color		color;
	t_obj		obj;
	double		t;
	t_vector	n;

	t = hit_object(ray, params.obj_set, &obj);
	if (t < T_MAX)
	{
		n = unit_vec(vec_diff(ray_at(ray, t), obj.sphere.coord));
		color = create_color_struct((int)((n.x + 1.0) * 0.5 * 256.0),\
		(int)((n.y + 1.0) * 0.5 * 256.0),\
		(int)((n.z + 1.0) * 0.5 * 256.0));
		return (color);
	}
	else
		return (create_color_struct(0, 0, 0));
}

int	main(int argc, char *argv[])
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_params	params;
	t_ray		ray;
	t_color		pixel_color;
	char		*file_contents;
	double		u;
	double		v;
	int			sample_size;

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
	free(file_contents);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGTH, "mini_rt");
	img.img = mlx_new_image(mlx, WIDTH, HEIGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits, &img.line, &img.endian);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGTH; j++)
		{
			pixel_color = create_color_struct(0, 0, 0);
			sample_size = 0;
			for (int k = i - 2; k <= i + 2; k++)
			{
				for (int l = j - 2; l <= j + 2; l++)
				{
					u = ((double)k / (WIDTH - 1.0) - 0.5) * VIEW_WIDTH;
					v = ((double)l / (HEIGTH - 1.0) - 0.5) * VIEW_HEIGTH;
					if (k >= 0 && k < WIDTH && l >= 0 && l < HEIGTH)
					{
						ray = ray_create(params.camera->coord, get_dir(u, v, *params.camera));
						pixel_color = color_add(pixel_color, ray_color(ray, params));
						sample_size++;
					}
				}
			}
			pixel_color.red = (double)pixel_color.red / (double)sample_size;
			pixel_color.green = (double)pixel_color.green / (double)sample_size;
			pixel_color.blue = (double)pixel_color.blue / (double)sample_size;
			put_pixel(&img, i, HEIGTH - j - 1, rgb_to_color(pixel_color));
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
