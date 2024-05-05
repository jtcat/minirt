/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:47:37 by psotto-m          #+#    #+#             */
/*   Updated: 2024/05/05 16:42:53 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../utils.h"
#include "libft.h"
#include "parser.h"
#include "../datatypes/matrix.h"
#include "../datatypes/argb.h"
#include "../datatypes/vec3.h"
#include "../render/rt.h"
#include "../intersect/primitives.h"

char	**parse_plane(t_rtctx *ctx, char **tokens)
{
	t_plane	*plane;

	plane = plane_new();
	if (!plane)
		return (error_helper("Out of memory!"));
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(plane));
	tokens = parse_transform(tokens, (t_node3d *)plane);
	if (!tokens)
		return (NULL);
	if (!parse_rgb(*(tokens++), &((t_primitive *)plane)->color))
		return (NULL);
	ctx->node_n++;
	return (tokens);
}

char	**parse_cylinder(t_rtctx *ctx, char **tokens)
{
	t_cylinder	*cyl;
	double	tmp;

	cyl = cylinder_new();
	if (!cyl)
		return (error_helper("Out of memory!"));
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(cyl));
	tokens = parse_transform(tokens, (t_node3d *)cyl);
	if (!tokens)
		return (error_helper("Bad cylinder transform"));
	if (!parse_double(*(tokens++), &tmp) || tmp < 0.0f)
		return (error_helper("Bad cylinder radius"));
	cyl->r = tmp / 2.0;
	if (!parse_double(*(tokens++), &tmp) || tmp < 0.0f)
		return (error_helper("Bad cylinder height"));
	cyl->h = tmp / 2.0;
	if (!parse_rgb(*(tokens++), &((t_primitive *)cyl)->color))
		return (error_helper("Bad cylinder color"));
	ctx->node_n++;
	return (tokens);
}

char	**error_helper(char *msg)
{
	print_err(msg);
	return (NULL);
}
