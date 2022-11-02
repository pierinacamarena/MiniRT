/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:03:22 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/02 14:46:15 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*filename == 'r')
		filename++;
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

	data = (t_data *)arg;
	if (keycode == ESC)
		close_mlx(data);
	else if (keycode == ENTER)
	{
		filename = data->file->filename;
		free_file(data->file);
		free_params(data->params);
		data->file = init_file(filename);
		if (data->file == NULL)
			close_mlx(data);
		data->params = parse(data->file->file_contents);
		if (data->params == NULL)
			close_mlx(data);
		data->img = replace_image(data->img, data);
		if (data->img == NULL)
			close_mlx(data);
	}
	return (0);
}

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
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, \
data->img->img, 0, 0);
	mlx_hook(data->mlx->mlx_win, 2, 1L << 0, keypress, data);
	mlx_hook(data->mlx->mlx_win, 17, 1L << 1, close_mlx, data);
	mlx_loop(data->mlx->mlx);
	return (0);
}
