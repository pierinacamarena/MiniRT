#include "free.h"

static void	free_objs_set(t_obj *obj_set)
{
	if (obj_set != NULL)
	{
		free_objs_set(obj_set->next);
		free(obj_set);
	}
}

void	free_params(t_params *params)
{
	if (params == NULL)
		return ;
	free(params->ambient);
	free(params->camera);
	free(params->light);
	free_objs_set(params->obj_set);
	free(params);
}

void	free_file(t_file *file)
{
	if (file == NULL)
		return ;
	close(file->fd);
	free(file->file_contents);
	free(file);
	file = NULL;
}

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
