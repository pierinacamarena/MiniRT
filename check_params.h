/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:25:38 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 15:24:34 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_PARAMS_H
# define CHECK_PARAMS_H

# include "vector.h"
# include "params.h"
# include "color.h"
# include "lexer.h"

# define U_LIMIT 1000000.0
# define L_LIMIT -1000000.0
# define COORD_LIMIT 0x1
# define ORIENT_LIMIT 0x2
# define LIGHT_RATIO_LIMIT 0x4
# define FOV_LIMIT 0x8
# define RGB_LIMIT 0x10
# define DIAMETER_LIMIT 0x100
# define HEIGHT_LIMIT 0x200
# define MISSING_CAM 0x20
# define MISSING_LIGHT 0x40
# define MISSING_AMBIENT 0x80
# define ZERO_ORIENT 0x400

int		check_coord_limit(t_vector coord);
int		check_orient_limit(t_vector orient);
int		check_light_ratio_limit(double light_ratio);
int		check_fov_limit(int fov);
int		check_rgb_limit(t_color rgb);
int		check_obj_set(t_obj *obj_set);
int		check_params(t_params *params);
void	print_param_error(int error);
void	print_token_error(const char *err_msg, int line, t_token token);

#endif
