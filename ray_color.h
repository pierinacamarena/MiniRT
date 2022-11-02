#ifndef RAY_COLOR_H
#define RAY_COLOR_H

#include "vector.h"
#include "params.h"
#include "ray.h"
#include "utils.h"
#include "hit.h"

#define POWER 100000.0

int	ray_color(t_ray ray, t_params params);

#endif
