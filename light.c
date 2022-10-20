/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:20:42 by pcamaren          #+#    #+#             */
/*   Updated: 2022/10/19 13:45:26 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

//light equation is Ld = kd(I/r^2)max(0,n.l)
t_vector	luminosity() {
	
}



// t_vector	get_luminosity(t_vars *vars, t_vector hit_point, \
// t_vector n_hit, float transmission)
// {
// 	t_vector	luminosity;
// 	t_vector	lum_dir;
// 	t_vector	p_lum;
// 	float		ld;
// 	float		la;

// 	eq_vector(&p_lum, sub_vector(vars->data.lum->pos, hit_point));
// 	eq_vector(&lum_dir, normalize(p_lum));
// 	if (transmission == FLT_MAX || transmission > norme(p_lum))
// 		transmission = 1;
// 	else
// 		transmission = 0.8;
// 	ld = transmission * (vars->data.lum->ratio * (1000000.0 / \
// 	scalaire_product(p_lum, p_lum))) * max(0, scalaire_product(n_hit, lum_dir));
// 	la = (100.0 * vars->data.luma->ratio);
// 	luminosity.x = 255 - (vars->data.lum->color.x * (ld / 255)) - \
// 	(vars->data.luma->color.x * (la / 255));
// 	luminosity.y = 255 - (vars->data.lum->color.y * (ld / 255)) - \
// 	(vars->data.luma->color.y * (la / 255));
// 	luminosity.z = 255 - (vars->data.lum->color.z * (ld / 255)) - \
// 	(vars->data.luma->color.z * (la / 255));
// 	return (luminosity);
// }
