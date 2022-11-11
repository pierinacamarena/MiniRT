/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:12:05 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/11 17:18:58 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	make_token(int type, t_scanner scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner.start;
	token.len = scanner.current - scanner.start;
	return (token);
}

static inline int	get_type(char *lexeme)
{	
	if (strcmp("A", lexeme) == 0)
		return (AMBIENT_TOKEN);
	else if (strcmp("C", lexeme) == 0)
		return (CAMERA_TOKEN);
	else if (strcmp("L", lexeme) == 0)
		return (LIGHT_TOKEN);
	else if (strcmp("sp", lexeme) == 0)
		return (SPHERE_TOKEN);
	else if (strcmp("pl", lexeme) == 0)
		return (PLANE_TOKEN);
	else if (strcmp("cy", lexeme) == 0)
		return (CYLINDER_TOKEN);
	else if (strcmp("spec", lexeme) == 0)
		return (SPECULAR_TOKEN);
	else
		return (ERROR_TOKEN);
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
	type = get_type(lexeme);
	free(lexeme);
	return (make_token(type, *scanner));
}

t_token	get_param_token(t_scanner *scanner)
{
	int	c;
	int	type;

	type = INT_TOKEN;
	c = advance(scanner);
	if (c == '+' || c == '-')
		c = advance(scanner);
	if (!ft_isdigit(c))
		return (make_token(ERROR_TOKEN, *scanner));
	while (ft_isdigit(c))
		c = advance(scanner);
	if (c == '.')
	{
		type = FLOAT_TOKEN;
		c = advance(scanner);
		if (!ft_isdigit(c))
			return (make_token(ERROR_TOKEN, *scanner));
	}
	while (ft_isdigit(c))
		c = advance(scanner);
	scanner->current--;
	if (len_scan(*scanner) > MAX_LEXEME_LEN)
		return (make_token(ERROR_LEN_TOKEN, *scanner));
	return (make_token(type, *scanner));
}

t_token	scan_token(t_scanner *scanner)
{
	skip_blanks(scanner);
	if (peek(*scanner) == '\0')
		return (make_token(EOF_TOKEN, *scanner));
	else if (isalpha(peek(*scanner)))
		return (get_id_token(scanner));
	else if (peek(*scanner) == ',')
	{
		advance(scanner);
		return (make_token(COMMA_TOKEN, *scanner));
	}
	else if (peek(*scanner) == '\n')
	{
		advance(scanner);
		return (make_token(NEWLINE_TOKEN, *scanner));
	}
	else
		return (get_param_token(scanner));
}
