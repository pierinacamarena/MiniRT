#include "hit.h"

static double	hit_sphere(t_ray ray, t_sphere sphere)
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

static double	hit_plane(t_ray ray, t_plane plane)
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

static double	hit_cylinder(t_ray ray, t_cylinder cylinder)
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
	right = unit_vec(vec_cross(unit_vec(cylinder.orient), vup));
	if (vec_dot(vup, right) != 0)
		right = unit_vec(vec_cross(unit_vec(cylinder.orient), vec_create(1, 0, 0)));
	up = unit_vec(vec_cross(right, unit_vec(cylinder.orient)));
	oc = vec_diff(ray.orig, cylinder.coord);
	a = pow(vec_dot(ray.dir, up), 2) + pow(vec_dot(ray.dir, right), 2);
	b = 2 * (vec_dot(right, oc) * vec_dot(right, ray.dir) + vec_dot(up, oc) * vec_dot(up, ray.dir));
	c = pow(vec_dot(right, oc), 2.0) + pow(vec_dot(up, oc), 2.0) - pow((cylinder.diameter / 2.0), 2);
	discr = pow(b, 2.0) - 4.0 * a * c;
	if (discr < 0.0)
		return (-1.0);
	t = (-1.0 * b - sqrt(discr)) / (2.0 * a);
	intersect = ray_at(ray, t);
	z = vec_dot(unit_vec(cylinder.orient), vec_diff(intersect, cylinder.coord));
	if ((z > 0.0 && z > cylinder.height / 2.0) || (z < 0.0 && z < -1.0 * cylinder.height / 2.0) || t < 0.0)
	{
		t = (-1.0 * b + sqrt(discr)) / (2.0 * a);
		intersect = ray_at(ray, t);
		z = vec_dot(unit_vec(cylinder.orient), vec_diff(intersect, cylinder.coord));
		if ((z > 0.0 && z > cylinder.height / 2.0) || (z < 0.0 && z < -1.0 * cylinder.height / 2.0))
		return (-1.0);
	}
	return (t);
}

double	hit_object(t_ray ray, t_obj *obj_set, t_obj *obj)
{
	double	t;
	double	temp;

	t = T_MAX;
	while (obj_set != NULL)
	{
		if (obj_set->type == SPHERE)
			temp = hit_sphere(ray, obj_set->sphere);
		else if (obj_set->type == PLANE)
			temp = hit_plane(ray, obj_set->plane);
		else if (obj_set->type == CYLINDER)
			temp = hit_cylinder(ray, obj_set->cylinder);
		if (temp > 0.0 && temp < t)
		{
			*obj = *obj_set;
			t = temp;
		}
		obj_set = obj_set->next;
	}
	return (t);
}
