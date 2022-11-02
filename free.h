/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:52:49 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/02 14:52:56 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include <stdlib.h>
# include <unistd.h>

# include "params.h"
# include "screen.h"

void	free_file(t_file *file);
void	free_params(t_params *params);
void	clean(t_data *data);
void	clean_params_exit(int exit_code, t_params *params);

#endif
