#include "ray.h"

t_ray	ray_create(t_vector orig, t_vector dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}

inline t_vector	ray_at(t_ray ray, double t)
{
	t_vector	point;

	point.x = ray.orig.x + ray.dir.x * t;
	point.y = ray.orig.y + ray.dir.y * t;
	point.z = ray.orig.z + ray.dir.z * t;
	return (point);
}

inline double	ray_length(t_ray ray)
{
	return (vec_length(vec_diff(ray.dir, ray.orig)));
}
