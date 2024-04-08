/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:45:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/07 02:12:41 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"
#include "parser.h"

bool	proc_line(t_rtctx *ctx, char **tokens)
{
	if (ft_strcmp(*tokens, "A") == 0)
		tokens = parse_ambient(ctx,++tokens);
	else if (ft_strcmp(*tokens, "C") == 0)
		tokens = parse_camera(ctx,++tokens);
	else if (ft_strcmp(*tokens, "L") == 0)
		tokens = parse_light(ctx,++tokens);
	else if (ft_strcmp(*tokens, "sp") == 0)
		tokens = parse_sphere(ctx,++tokens);
	else if (ft_strcmp(*tokens, "pl") == 0)
		tokens = parse_plane(ctx,++tokens);
	else if (ft_strcmp(*tokens, "cy") == 0)
		tokens = parse_cylinder(ctx,++tokens);
	else
	{
		print_err("Unrecognized primitive");
		return (false);
	}
	if (tokens && *tokens)
	{
		print_err("Too many tokens on a line");
		return (false);
	}
	return (true);
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
