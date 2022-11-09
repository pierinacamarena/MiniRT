/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:40:59 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:41:23 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "ray.h"
# include "params.h"

typedef struct s_vars {
	t_vector	oc;
	t_vector	vup;
	t_vector	right;
	t_vector	up;
	t_vector	intersect;
	double		a;
	double		b;
	double		c;
	double		t;
	double		z;
	double		discr;
}	t_vars;

double	hit_object(t_ray, t_obj *obj_set, t_obj *obj);
void	set_vectors(t_ray ray, t_cylinder cylinder, t_vars *var);
void	set_doubles(t_ray ray, t_cylinder cylinder, t_vars *var);

#endif
