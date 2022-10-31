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

int	rgb_to_color(t_color rgb)
{
	return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
}

int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}
