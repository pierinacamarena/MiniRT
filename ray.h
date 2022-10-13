#ifndef RAY_H
#define RAY_h

#include "vector.h"

typedef struct s_ray {
	t_vector	orig;
	t_vector	dir;
}	t_ray;

t_ray		ray_create(t_vector orig, t_vector dir);
t_vector	ray_at(t_ray ray, double t);
double		ray_length(t_ray ray);

#endif
