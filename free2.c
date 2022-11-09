/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:43:26 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 16:43:27 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	free_obj_set(t_obj *obj_set)
{
	if (obj_set != NULL)
	{
		free_obj_set(obj_set->next);
		free(obj_set);
		obj_set = NULL;
	}
}

void	free_params(t_params *params)
{
	if (params == NULL)
		return ;
	free(params->ambient);
	free(params->camera);
	free(params->light);
	free_obj_set(params->obj_set);
	free(params);
	params = NULL;
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
