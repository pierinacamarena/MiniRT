/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:50:17 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 11:08:52 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	free_img(t_img *img, t_mlx *mlx)
{
	if (img == NULL || mlx == NULL)
		return ;
	mlx_destroy_image(mlx->mlx, img->img);
	free(img);
	img = NULL;
}

static void	free_mlx(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
	mlx = NULL;
}

void	clean_params_exit(int exit_code, t_params *params)
{
	free_params(params);
	exit(exit_code);
}

void	clean(t_data *data)
{
	if (data == NULL)
		return ;
	free_file(data->file);
	free_params(data->params);
	free_img(data->img, data->mlx);
	free_mlx(data->mlx);
	free(data);
}

void	clean_data_exit(int exit_code, t_data *data)
{
	clean(data);
	exit(exit_code);
}
