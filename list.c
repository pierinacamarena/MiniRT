/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:43:55 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 16:43:56 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_obj	*append_obj_set(t_obj *obj_set, t_obj *obj)
{
	if (obj_set == NULL)
		return (obj);
	else
		obj_set->next = append_obj_set(obj_set->next, obj);
	return (obj_set);
}
