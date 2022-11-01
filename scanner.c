#include "scanner.h"

void	init_scanner(t_scanner *scanner, const char *s)
{
	scanner->start = s;
	scanner->current = s;
}

int	advance(t_scanner *scanner)
{
	int	c;

	c = *scanner->current;
	scanner->current++;
	return (c);
}

int	peek(t_scanner scanner)
{
	return (*scanner.current);
}

int	len_scan(t_scanner scanner)
{
	return ((int)(scanner.current - scanner.start));
}

void	skip_blanks(t_scanner *scanner)
{
	while (isblank(peek(*scanner)))
		advance(scanner);
	scanner->start = scanner->current;
}
