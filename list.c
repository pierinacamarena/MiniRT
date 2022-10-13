#include "list.h"

t_obj	*append_obj_set(t_obj *obj_set, t_obj *obj)
{
	if (obj_set == NULL)
		return (obj);
	else
		obj_set->next = append_obj_set(obj_set->next, obj);
	return (obj_set);
}
