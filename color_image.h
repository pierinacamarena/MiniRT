/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_image.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:49:42 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/02 14:49:57 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_IMAGE_H
# define COLOR_IMAGE_H

# include "params.h"
# include "screen.h"
# include "ray.h"
# include "ray_color.h"

void	color_image(t_params *params, t_img *img);
t_img	*replace_image(t_img *old_img, t_data *data);

#endif
