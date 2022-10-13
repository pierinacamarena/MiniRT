#include "free.h"

void	free_objs_set(t_obj *obj_set)
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
}

void	clean_exit(int exit_code, t_params *params)
{
	free_params(params);
	exit(exit_code);
}
