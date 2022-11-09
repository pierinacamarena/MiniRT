/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:47:14 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 17:47:18 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <ctype.h>

typedef struct s_scanner {
	const char	*start;
	const char	*current;
}	t_scanner;

void	init_scanner(t_scanner *scanner, const char *s);
int		advance(t_scanner *scanner);
int		peek(t_scanner scanner);
int		len_scan(t_scanner scanner);
void	skip_blanks(t_scanner *scanner);

#endif
