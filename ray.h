/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:47:00 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:47:05 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_ray {
	t_vector	orig;
	t_vector	dir;
}	t_ray;

t_ray		ray_create(t_vector orig, t_vector dir);
t_vector	ray_at(t_ray ray, double t);
double		ray_length(t_ray ray);

#endif
