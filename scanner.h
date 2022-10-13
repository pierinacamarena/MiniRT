#ifndef SCANNER_H
#define SCANNER_H

#include <ctype.h>

typedef struct s_scanner {
	char	*start;
	char	*current;
}	t_scanner;

void	init_scanner(t_scanner *scanner, char *s);
int		advance(t_scanner *scanner);
int		peek(t_scanner scanner);
int		len_scan(t_scanner scanner);
void	skip_blanks(t_scanner *scanner);

#endif
