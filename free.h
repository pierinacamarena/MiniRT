#ifndef FREE_H
#define FREE_H

#include <stdlib.h>
#include <unistd.h>

#include "params.h"
#include "screen.h"

void	free_file(t_file *file);
void	free_params(t_params *params);
void	clean(t_data *data);
void	clean_params_exit(int exit_code, t_params *params);

#endif
