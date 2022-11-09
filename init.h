/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:42:05 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:42:06 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <string.h>

# include "utils.h"
# include "screen.h"
# include "free.h"
# include "parse.h"

# define BUFSIZE 4096

t_file	*init_file(const char *filename);
t_data	*init_data(const char *filename);

#endif
