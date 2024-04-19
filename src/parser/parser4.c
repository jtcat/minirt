/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:47:37 by psotto-m          #+#    #+#             */
/*   Updated: 2024/04/18 15:47:38 by psotto-m         ###   ########.fr       */
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

char	**parse_cylinder(t_rtctx *ctx, char **tokens)
{
	t_primitive	*cyl;
	float		tmp;

	cyl = malloc(sizeof(t_primitive));
	cyl->spec = malloc(sizeof(t_cylinder));
	if (!cyl || !cyl->spec)
		return (NULL);
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(cyl));
	tokens = parse_transform(tokens, &cyl->transf);
	if (!tokens)
		return (NULL);
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->r = tmp / 2.0;
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->h = tmp / 2.0;
	if (!parse_rgb(*(tokens++), &cyl->color))
		return (NULL);
	cyl->intersect = i_cylinder;
	++ctx->prim_n;
	return (tokens);
}

char	**parse_plane(t_rtctx *ctx, char **tokens)
{
	t_primitive	*plane;

	plane = malloc(sizeof(t_primitive));
	plane->spec = malloc(sizeof(t_plane));
	if (!plane || !plane->spec)
		return (NULL);
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(plane));
	tokens = parse_transform(tokens, &plane->transf);
	if (!tokens)
		return (NULL);
	if (!parse_rgb(*(tokens++), &plane->color))
		return (NULL);
	plane->intersect = i_plane;
	++ctx->prim_n;
	return (tokens);
}

char	**error_helper(char *msg)
{
	print_err(msg);
	return (NULL);
}
