#include "lexer.h"

static t_token	make_token(int type, t_scanner scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner.start;
	token.len = scanner.current - scanner.start;
	return (token);
}

t_token	get_id_token(t_scanner *scanner)
{
	char	*lexeme;
	int		type;

	while (!isspace(peek(*scanner)))
		advance(scanner);
	lexeme = strndup(scanner->start, len_scan(*scanner));
	if (lexeme == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (strcmp("A", lexeme) == 0)
		type = AMBIENT_TOKEN;
	else if (strcmp("C", lexeme) == 0)
		type = CAMERA_TOKEN;
	else if (strcmp("L", lexeme) == 0)
		type = LIGHT_TOKEN;
	else if (strcmp("sp", lexeme) == 0)
		type = SPHERE_TOKEN;
	else if (strcmp("pl", lexeme) == 0)
		type = PLANE_TOKEN;
	else if (strcmp("cy", lexeme) == 0)
		type = CYLINDER_TOKEN;
	else
		type = ERROR_TOKEN;
	free(lexeme);
	return (make_token(type, *scanner));
}

t_token	get_param_token(t_scanner *scanner)
{
	int	c;
	int	type;

	type = INT_TOKEN;
	c = advance(scanner);
	if (c == ',')
		return (make_token(COMMA_TOKEN, *scanner));
	else if (c == '\n')
		return (make_token(NEWLINE_TOKEN, *scanner));
	if (c == '+' || c == '-')
		c = advance(scanner);
	if (!isdigit(c))
		return (make_token(ERROR_TOKEN, *scanner));
	while (isdigit(c))
		c = advance(scanner);
	if (c == '.')
	{
		type = FLOAT_TOKEN;
		c = advance(scanner);
	}
	while (isdigit(c))
		c = advance(scanner);
	scanner->current--;
	return (make_token(type, *scanner));
}

/*
	scans the next token in input
	tokens are sequences of characters separated by spaces
*/

t_token	scan_token(t_scanner *scanner)
{
	skip_blanks(scanner);
	//add handling of multiple buffers
	if (peek(*scanner) == '\0')
		return (make_token(EOF_TOKEN, *scanner));
	else if (isalpha(peek(*scanner)))
		return (get_id_token(scanner));
	else
		return (get_param_token(scanner));
}
