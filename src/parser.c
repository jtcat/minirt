/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:45:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 00:56:39 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdbool.h>

bool	proc_line(t_rtctx *ctx, char **tokens)
{
	bool	valid;

	if (ft_strcmp(*tokens, "A") == 0)
		valid = parse_ambient(ctx, ++tokens);
	else if (ft_strcmp(*tokens, "C") == 0)
		valid = parse_camera(ctx, ++tokens);
	else if (ft_strcmp(*tokens, "L") == 0)
		valid = parse_light(ctx, ++tokens);
	else if (ft_strcmp(*tokens, "sp") == 0)
		valid = parse_sphere(ctx, ++tokens);
	else if (ft_strcmp(*tokens, "pl") == 0)
		valid = parse_plane(ctx, ++tokens);
	else if (ft_strcmp(*tokens, "cy") == 0)
		valid = parse_cylinder(ctx, ++tokens);
	else
	{
		print_err("Unrecognized primitive");
		return (false);
	}
	if (valid && *tokens)
	{
		print_err("Too many tokens on a line");
		return (false);
	}
	return (valid);
}

bool	parser_main(t_rtctx *ctx, int fd)
{
	char	*line;
	char	**tokens;
	bool	valid;

	line = get_next_line(fd);
	valid = true;
	while (line)
	{
		tokens = ft_split(line, ' ');
		if (tokens && *tokens)
			valid = proc_line(ctx, tokens);
		free_ptrarr((void **)tokens);
		free(line);
		if (!valid)
			break;
		line = get_next_line(fd);
	}
	close(fd);
	return (valid);
}
