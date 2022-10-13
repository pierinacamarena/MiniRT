#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"

#define AMBIENT_TOKEN 0x1
#define CAMERA_TOKEN 0x2
#define LIGHT_TOKEN 0x4
#define SPHERE_TOKEN 0x8
#define PLANE_TOKEN 0x10
#define CYLINDER_TOKEN 0x20
#define INT_TOKEN 0x40
#define FLOAT_TOKEN 0x80
#define COMMA_TOKEN 0x100
#define NEWLINE_TOKEN 0x200
#define ERROR_TOKEN -2
#define EOF_TOKEN -1

typedef struct s_token {
	int		type;
	char	*start;
	int		len;
}	t_token;

t_token	scan_token(t_scanner *scanner);

#endif
