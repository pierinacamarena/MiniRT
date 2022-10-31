#ifndef SCREEN_H
#define SCREEN_H

#include "params.h"

#define RATIO (16.0 / 9.0)
#define WIDTH 300
#define HEIGTH ((double)WIDTH / RATIO)
#define FOCAL_LEN 1.0
# define ESC	65307

typedef struct s_data {
	t_params	*params;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits;
	int			line;
	int			endian;
}	t_data;

void	put_pixel(t_data *data, int x, int y, int color);

#endif
