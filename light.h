/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:20:38 by pcamaren          #+#    #+#             */
/*   Updated: 2022/11/11 17:15:55 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "params.h"

double	calc_specular(t_params params, t_vector dir_light, t_vector n_hit, \
t_vector p_hit);
double	light_dot_normal(t_params params, t_vector p_hit, t_vector n_hit, \
t_obj *obj);
int		is_in_shadow(t_vector p_hit, t_vector n_hit, t_params params);

#endif
