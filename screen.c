#include "screen.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}
