#include <mlx.h>

#include "screen.h"
#include "params.h"
#include "parse.h"
#include "init.h"
#include "color_image.h"
#include "free.h"

void	check_filename(char *filename)
{
	while (ft_isalnum(*filename) || *filename == '_')
		filename++;
	if (*filename == '.')
		filename++;
	if (*filename == 'r') filename++;
	if (*filename == 't')
		filename++;
	if (*filename != '\0')
	{
		printf("File name must contain only alphanumerical characters and '_' \
and must end in .rt\n");
		exit(EXIT_FAILURE);
	}
}

int	close_mlx(t_data *data)
{
	mlx_loop_end(data->mlx->mlx);
	clean(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	keypress(int keycode, void *arg)
{
	t_data		*data;
	const char	*filename;
	t_img		*img;

	data = (t_data *)arg;
	if (keycode == ESC)
		close_mlx(data);
	else if (keycode == ENTER)
	{
		filename = data->file->filename;
		free_file(data->file);
		data->file = init_file(filename);
		if (data->file == NULL)
			close_mlx(data);
		free_params(data->params);
		data->params = parse(data->file->file_contents);
		if (data->params == NULL)
			close_mlx(data);
		img = get_new_image(data->mlx);
		if (img == NULL)
			close_mlx(data);
		color_image(data->params, img);
		mlx_destroy_image(data->mlx->mlx, data->img->img);
		data->img = img;
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->img->img, 0, 0);
	}
	return (0);
}

/*	1) get the file contents
	2) parse the file contents
	3) start the mlx
	4) create an image
	5) color the image
	6) put the image on the screen
*/

int	main(int argc, char *argv[])
{
	t_data		*data;

	if (argc != 2)
	{
		printf("Invalid number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	check_filename(argv[1]);
	data = init_data(argv[1]);
	if (data == NULL)
		exit(EXIT_FAILURE);
	color_image(data->params, data->img);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->img->img, 0, 0);
	mlx_hook(data->mlx->mlx_win, 2, 1L<<0, keypress, data);
	mlx_hook(data->mlx->mlx_win, 17, 1L<<1, close_mlx, data);
	mlx_loop(data->mlx->mlx);
	return (0);
}
