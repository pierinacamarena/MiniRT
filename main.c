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

double			max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double			min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

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

t_vector	get_dir(double u, double v, t_camera camera)
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

double	hit_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		t;

	oc = vec_diff(ray.orig, sphere.coord);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0 * vec_dot(oc, ray.dir);
	c = vec_dot(oc , oc) - pow(sphere.diameter / 2.0, 2.0);
	discr = pow(b, 2.0) - 4.0 * a * c;
	if (discr < 0.0)
		return (-1);
	t = (b * -1.0 - sqrt(discr)) / (2.0 * a);
	if (t < 0.0)
		t = (b * -1.0 + sqrt(discr)) / (2.0 * a);
	return (t);
}

double	hit_plane(t_ray ray, t_plane plane)
{
	double		t;

	if (vec_dot(plane.orient, ray.dir) != 0)
	{
		t = vec_dot(plane.orient, vec_diff(plane.coord, ray.orig));
		t /= vec_dot(plane.orient, ray.dir);
	}
	else
		t = T_MAX;
	return (t);
}

double	hit_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		z;
	double		discr;
	double		t;
	t_vector	vup;
	t_vector	right;
	t_vector	up;
	t_vector	intersect;

	vup = vec_create(0, 1, 0);
	right = unit_vec(vec_cross(cylinder.orient, vup));
	if (vec_dot(vup, right) != 0)
		right = unit_vec(vec_cross(cylinder.orient, vec_create(1, 0, 0)));
	up = unit_vec(vec_cross(right, cylinder.orient));
	oc = vec_diff(ray.orig, cylinder.coord);
	a = pow(vec_dot(ray.dir, up), 2) + pow(vec_dot(ray.dir, right), 2);
	b = 2 * (vec_dot(right, oc) * vec_dot(right, ray.dir) + vec_dot(up, oc) * vec_dot(up, ray.dir));
	c = pow(vec_dot(right, oc), 2.0) + pow(vec_dot(up, oc), 2.0) - pow((cylinder.diameter / 2.0), 2);
	discr = pow(b, 2.0) - 4.0 * a * c;
	if (discr < 0.0)
		return (-1.0);
	t = (-1.0 * b - sqrt(discr)) / (2.0 * a);
	intersect = vec_add(ray.orig, vec_scale(ray.dir, t));
	z = vec_dot(cylinder.orient, vec_diff(intersect, cylinder.coord));
	if ((z > 0.0 && z > cylinder.height / 2.0) || (z < 0.0 && z < -1.0 * cylinder.height / 2.0) || t < 0.0)
	{
		t = (-1.0 * b + sqrt(discr)) / (2.0 * a);
		intersect = vec_add(ray.orig, vec_scale(ray.dir, t));
		z = vec_dot(cylinder.orient, vec_diff(intersect, cylinder.coord));
		if ((z > 0.0 && z > cylinder.height / 2.0) || (z < 0.0 && z < -1.0 * cylinder.height / 2.0))
		return (-1.0);
	}
	return (t);
}

double	calculate_shadow(t_params param, t_vector p_hit, t_vector n_hit)
{
	t_vector	dir_light;
	double		intensity;
	intensity = 0;

	dir_light = vec_diff(param.light->coord, p_hit);
	intensity = 255 * max(0, vec_dot(unit_vec(dir_light), n_hit))* 2500 / vec_dot(dir_light, dir_light);
	return (intensity);
}


double	hit_object(t_ray ray, t_obj *obj_set, t_obj *obj, t_vector *p_hit, t_vector *n_hit)
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
				*p_hit = ray_at(ray, t);
				*n_hit = unit_vec(vec_diff(*p_hit, obj->sphere.coord));
				// if ((vec_length(vec_diff(params.camera->coord, obj->sphere.coord))) < (obj->sphere.diameter/2))
				// 	*n_hit = vec_scale(*n_hit, -1);
			}
		}
		else if (obj_set->type == PLANE)
		{
			temp = hit_plane(ray, obj_set->plane);
			if (temp > 0.0 && temp < t)
			{
				*obj = *obj_set;
				t = temp;
			}
		}
		else if (obj_set->type == CYLINDER)
		{
			temp = hit_cylinder(ray, obj_set->cylinder);
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
	//t_color		color;
	t_obj		obj;
	double		t;
	t_vector	p_hit;
	t_vector	n_hit;
	double			lum;
	double			red;
	double			green;
	double			blue;
	//t_vector	n;

	t = hit_object(ray, params.obj_set, &obj, &p_hit, &n_hit);
	if (t < T_MAX)
	{
		/*n = unit_vec(vec_diff(ray_at(ray, t), obj.sphere.coord));
		color = create_color_struct((int)((n.x + 1.0) * 0.5 * 256.0),\
		(int)((n.y + 1.0) * 0.5 * 256.0),\
		(int)((n.z + 1.0) * 0.5 * 256.0));*/
		if (obj.type == SPHERE)
		{
			lum = calculate_shadow(params, p_hit, n_hit);
			
			red = min(255,(max(50.0, lum)));
			// printf("red = %f\n", red);
			// green = min(255,(max(0.0, lum)));
			green = 0;
			// printf("green = %f\n", green);
			// blue = min(255,(max(0.0, lum)));
			blue = 0;
			// printf("blue = %f\n", blue);
			return (create_color_struct((int)red, (int)green, (int)blue));
			// return (obj.sphere.rgb);
		}
		else if (obj.type == PLANE)
			return (obj.plane.rgb);
		else if (obj.type == CYLINDER)
			return (obj.cylinder.rgb);
	}
	return (create_color_struct(0, 0, 0));
}

void	test_sphere(t_ray ray, t_params params)
{
	t_sphere sphere = params.obj_set->sphere;

	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		t;

	oc = vec_diff(ray.orig, sphere.coord);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0 * vec_dot(oc, ray.dir);
	c = vec_dot(oc , oc) - pow(sphere.diameter / 2.0, 2.0);
	discr = pow(b, 2.0) - 4.0 * a * c;
	t = (b * -1.0 - sqrt(discr)) / (2.0 * a);
	if (t < 0.0)
		t = (b * -1.0 + sqrt(discr)) / (2.0 * a);
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
	free(file_contents);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGTH, "mini_rt");
	img.img = mlx_new_image(mlx, WIDTH, HEIGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits, &img.line, &img.endian);
	theta = degree_to_radian(params.camera->fov);
	view_width = 2.0 * tan(theta / 2.0) * FOCAL_LEN;
	view_height = view_width / RATIO;	
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGTH; j++)
		{
			pixel_color = create_color_struct(0, 0, 0);
			u = ((double)i / (WIDTH - 1.0) - 0.5) * view_width;
			v = ((double)j / (HEIGTH - 1.0) - 0.5) * view_height;
			ray = ray_create(params.camera->coord, get_dir(u, v, *params.camera));
			if (i == (int)(WIDTH / 2) && j == (int)(HEIGTH / 2))
				test_sphere(ray, params);
			pixel_color = color_add(pixel_color, ray_color(ray, params));
			put_pixel(&img, i, HEIGTH - j - 1, rgb_to_color(pixel_color));
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
