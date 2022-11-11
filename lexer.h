/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:42:53 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 16:58:00 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# include "scanner.h"
# include "utils.h"

# define AMBIENT_TOKEN 0x1
# define CAMERA_TOKEN 0x2
# define LIGHT_TOKEN 0x4
# define SPHERE_TOKEN 0x8
# define PLANE_TOKEN 0x10
# define CYLINDER_TOKEN 0x20
# define SPECULAR_TOKEN 0x400
# define INT_TOKEN 0x40
# define FLOAT_TOKEN 0x80
# define COMMA_TOKEN 0x100
# define NEWLINE_TOKEN 0x200
# define ERROR_LEN_TOKEN -3
# define ERROR_TOKEN -2
# define EOF_TOKEN -1
# define MAX_LEXEME_LEN 8

typedef struct s_token {
	int			type;
	const char	*start;
	int			len;
}	t_token;

t_token	scan_token(t_scanner *scanner);

#endif
