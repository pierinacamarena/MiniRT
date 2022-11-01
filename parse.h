#ifndef PARSE_H
#define PARSE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "lexer.h"
#include "params.h"
#include "free.h"
#include "list.h"
#include "utils.h"

#define ID 256
#define PARAM 257

typedef struct s_parse_utils {
	t_token		token;
	t_scanner	scanner;
	int			line;
}	t_parse_utils;

t_params	*parse(const char *s);

#endif
