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
	free(params->ambient);
	free(params->camera);
	free(params->light);
	free_objs_set(params->obj_set);
	free(params);
}

void	free_file(t_file *file)
{
	close(file->fd);
	free(file->file_contents);
	free(file);
}

static void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	clean_params_exit(int exit_code, t_params *params)
{
	free_params(params);
	exit(exit_code);
}

void	clean(t_data *data)
{
	if (data->params != NULL)
		free_params(data->params);
	if (data->file != NULL)
		free_file(data->file);
	if (data->img != NULL)
		mlx_destroy_image(data->mlx->mlx, data->img->img);
	if (data->mlx != NULL)
		free_mlx(data->mlx);
}
