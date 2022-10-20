#ifndef SCREEN_H
#define SCREEN_H

#define RATIO (16.0 / 9.0)
#define WIDTH 1050
#define HEIGTH ((double)WIDTH / RATIO)
#define FOCAL_LEN 1.0

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits;
	int		line;
	int		endian;
}	t_data;

void	put_pixel(t_data *data, int x, int y, int color);

#endif
