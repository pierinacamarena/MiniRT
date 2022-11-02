/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:46:35 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/02 14:47:18 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	create_color_struct(int red, int green, int blue)
{
	t_color	color;

	color.red = red;
	color.green = green;
	color.blue = blue;
	return (color);
}

t_color	color_add(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.red = color1.red + color2.red;
	new_color.green = color1.green + color2.green;
	new_color.blue = color1.blue + color2.blue;
	return (new_color);
}

int	create_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}
