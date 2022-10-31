#ifndef COLOR_H
#define COLOR_H

typedef struct	s_color {
	int	red;
	int	green;
	int	blue;
}	t_color;

t_color	create_color_struct(int red, int green, int blue);
t_color	color_add(t_color color1, t_color color2);
int		create_color(int red, int green, int blue);
int		rgb_to_color(t_color rgb);
int		get_r(int color);
int		get_g(int color);
int		get_b(int color);

#endif
