/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:46:17 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:46:28 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>

# include "scanner.h"
# include "lexer.h"
# include "params.h"
# include "free.h"
# include "list.h"
# include "utils.h"
# include "check_params.h"

typedef struct s_parse_utils {
	t_token		token;
	t_scanner	scanner;
	int			line;
	int			panic;
}	t_parse_utils;

t_params	*parse(const char *s);

/* init_obj2 */
void		get_ambient_light(t_params *params, t_parse_utils *utils);
void		get_camera(t_params *params, t_parse_utils *utils);
void		get_light(t_params *params, t_parse_utils *utils);

/* init_obj1 */
void		get_sphere(t_params *params, t_parse_utils *utils);
void		get_plane(t_params *params, t_parse_utils *utils);
void		get_cylinder(t_params *params, t_parse_utils *utils);

/* parse_utils */
int			get_int(t_token token, t_params *params);
double		get_float(t_token token, t_params *params);
t_token		match(int type, t_parse_utils *utils);
void		get_object(t_params *params, t_parse_utils *utils);

/* init_obj_utils */
void		get_coord(t_obj *obj, t_params *params, t_parse_utils *utils);
void		get_cam_coord(t_params *params, t_parse_utils *utils);
void		get_light_coord(t_params *params, t_parse_utils *utils);
void		get_orient(t_obj *obj, t_params *params, t_parse_utils *utils);
void		get_surf_rgb(t_obj *obj, t_params *params, t_parse_utils *utils);

#endif
