/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:21:13 by rbourdil          #+#    #+#             */
/*   Updated: 2022/11/09 11:36:18 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_params	*parse(const char *s)
{
	t_params		*params;
	t_parse_utils	utils;
	int				error;

	params = (t_params *)malloc(sizeof(t_params));
	if (params == NULL)
		return (NULL);
	bzero(params, sizeof(t_params));
	utils.line = 1;
	init_scanner(&utils.scanner, s);
	utils.token = scan_token(&utils.scanner);
	utils.panic = 0;
	get_object(params, &utils);
	error = check_params(params);
	if (utils.panic == 1 || error != 0)
	{
		free_params(params);
		if (utils.panic != 1)
			print_param_error(error);
		return (NULL);
	}
	return (params);
}
