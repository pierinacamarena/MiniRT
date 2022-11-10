/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:47:27 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:55:00 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

# include <mlx.h>
# include <stdlib.h>

# include "params.h"

# define RATIO 1.7777777
# define WIDTH 1050
# define FOCAL_LEN 1.0
# define ESC	65307
# define ENTER 65293

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits;
	int		line;
	int		endian;
}	t_img;

typedef struct s_file {
	const char	*filename;
	int			fd;
	char		*file_contents;
}	t_file;

typedef struct s_data {
	t_file		*file;
	t_params	*params;
	t_mlx		*mlx;
	t_img		*img;
}	t_data;

void	put_pixel(t_img *img, int x, int y, int color);
t_mlx	*start_mlx(void);
t_img	*get_new_image(const t_mlx *mlx);
t_img	*replace_image(t_img *old_image, t_data *data);

#endif
