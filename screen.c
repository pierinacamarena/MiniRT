/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:44:31 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:56:45 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bits / 8));
	*(unsigned int *)dst = color;
}

t_mlx	*start_mlx(void)
{
	t_mlx	*mlx;
	double	height;

	height = WIDTH / RATIO;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		printf("mlx_init() failed.\n");
		free(mlx);
		return (NULL);
	}
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, height, "mini_rt");
	if (mlx->mlx_win == NULL)
	{
		printf("mlx_win() failed.\n");
		free(mlx->mlx);
		free(mlx);
		return (NULL);
	}
	return (mlx);
}

t_img	*get_new_image(const t_mlx *mlx)
{
	t_img	*img;
	double	height;

	height = WIDTH / RATIO;
	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	img->img = mlx_new_image(mlx->mlx, WIDTH, height);
	if (img->img == NULL)
	{
		printf("mlx_new_image() failed.\n");
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits, &img->line, \
&img->endian);
	return (img);
}
