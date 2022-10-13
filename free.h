#ifndef FREE_H
#define FREE_H

#include <stdlib.h>

#include "params.h"

void	free_objs_set(t_obj *objs_set);
void	free_params(t_params *params);
void	clean_exit(int exit_code, t_params *params);

#endif
