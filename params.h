/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:45:36 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:46:01 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

# include "color.h"
# include "vector.h"

# define SPHERE 0x1
# define CYLINDER 0x2
# define PLANE 0x4
# define T_MAX 10000000
# define PI 3.14159265358979

typedef struct s_ambient {
	double	ambient_ratio;
	t_color	rgb;
}	t_ambient;

typedef struct s_camera {
	t_vector	coord;
	t_vector	orient;
	int			fov;
}	t_camera;

typedef struct s_light {
	t_vector	coord;
	double		bright_ratio;
	t_color		rgb;
}	t_light;

typedef struct s_sphere {
	t_vector	coord;
	double		diameter;
	t_color		rgb;
}	t_sphere;

typedef struct s_cylinder {
	t_vector	coord;
	t_vector	orient;
	double		diameter;
	double		height;
	t_color		rgb;
}	t_cylinder;

typedef struct s_plane {
	t_vector	coord;
	t_vector	orient;
	t_color		rgb;
}	t_plane;

typedef struct s_obj {
	int				type;
	union {
		t_sphere	sphere;
		t_cylinder	cylinder;
		t_plane		plane;
	};
	struct s_obj	*next;
}	t_obj;

typedef struct s_params {
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_obj		*obj_set;
	double		view_width;
	double		view_height;
}	t_params;	

#endif
