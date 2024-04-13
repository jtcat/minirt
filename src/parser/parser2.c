/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:03:48 by jcat              #+#    #+#             */
/*   Updated: 2024/04/08 23:53:22 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../utils.h"
#include "parser.h"
#include "../datatypes/matrix.h"
#include "../datatypes/argb.h"
#include "../datatypes/vec3.h"
#include "../render/rt.h"
#include "../intersect/primitives.h"

// Top level token parsers like parse_float should
// print their own errors and return NULL
//
char	**parse_ambient(t_rtctx *ctx, char **tokens)
{
	if (ctx->ambient.r > -1)
		return(error_helper("Ambient light was redefined"));
	if (!parse_float(*(tokens++), &ctx->ambient_f))
		return(error_helper("Malformed Floar"));
	if (ctx->ambient_f < 0.0f || ctx->ambient_f > 1.0f)
		return(error_helper("Ambient ratio out of range (0.0 - 1.0)"));
	if (!parse_rgb(*(tokens++), &ctx->ambient))
		return (error_helper("Malformed RGB"));
	return (tokens);
}

char	**parse_camera(t_rtctx *ctx, char **tokens)
{
	int	fov;

	if (ctx->cam.hfov > -1.0)
	{
		("Camera was redefined");
		return (NULL);
	}
	if (!parse_vec3(*(tokens++), &ctx->cam.lookfrom))
		return (NULL);
	if (!parse_vec3(*(tokens++), &ctx->cam.lookdir)
		|| !is_normal(&ctx->cam.lookdir))
		return (NULL);
	if (!parse_int(*(tokens++), &fov))
		return (NULL);
	if (fov < 0 || fov > 180)
	{
		print_err("Camera FOV out of range (0 - 180)");
		return (NULL);
	}
	ctx->cam.hfov = (double)fov / 360.0f * 2 * M_PI;
	return (tokens);
}

char	**parse_transform(char **tokens, t_transf *t)
{
	t_vec3	pos;
	t_vec3	dir;

	if (!parse_vec3(*(tokens++), &pos))
		return (NULL);
	if (!parse_vec3(*(tokens++), &dir) || !is_normal(&dir))
		return (NULL);
	tf_look_up(&pos, &dir, t);
	return (tokens);
}

char	**parse_light(t_rtctx *ctx, char **tokens)
{
	if (ctx->light.f > 0)
		return(error_helper("Light was redefined"));
	if (!parse_vec3(*(tokens++), &ctx->light.pos))
		return(error_helper("Missing point light position"));
	if (!parse_float(*(tokens++), &ctx->light.f))
		return(error_helper("Error in Float"));
	if (ctx->light.f < 0.0f || ctx->light.f > 1.0f)
		return(error_helper("Light intensity out of range (0.0 - 1.0)"));
	if (!parse_rgb(*(tokens++), &ctx->light.color))
		return(error_helper("Missing point light color"));
	return (tokens);
}

char	**parse_sphere(t_rtctx *ctx, char **tokens)
{
	t_vec3		tmpv;
	t_primitive	*sphere;
	float		radius;

	sphere = malloc(sizeof(t_primitive));
	sphere->spec = malloc(sizeof(t_sphere));
	if (!sphere || !sphere->spec)
		return (NULL);
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	tf_from_pos(&tmpv, &sphere->transf);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (NULL);
	((t_sphere *)sphere->spec)->radius = radius / 2.0f;
	if (!parse_rgb(*(tokens++), &sphere->color))
		return (NULL);
	sphere->intersect = i_sphere;
	ft_lstadd_back(&ctx->prims, ft_lstnew(sphere));
	return (tokens);
}

char	**parse_plane(t_rtctx *ctx, char **tokens)
{
	t_primitive	*plane;

	plane = malloc(sizeof(t_primitive));
	plane->spec = NULL;
	if (!plane)
		return (NULL);
	tokens = parse_transform(tokens, &plane->transf);
	if (!tokens)
		return (NULL);
	if (!parse_rgb(*(tokens++), &plane->color))
		return (NULL);
	plane->intersect = i_plane;
	ft_lstadd_back(&ctx->prims, ft_lstnew(plane));
	return (tokens);
}

char	**parse_cylinder(t_rtctx *ctx, char **tokens)
{
	t_primitive	*cyl;
	float		tmp;

	cyl = malloc(sizeof(t_primitive));
	cyl->spec = malloc(sizeof(t_cylinder));
	if (!cyl || !cyl->spec)
		return (NULL);
	tokens = parse_transform(tokens, &cyl->transf);
	if (!tokens)
		return (NULL);
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->radius = tmp / 2.0;
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->height = tmp / 2.0;
	if (!parse_rgb(*(tokens++), &cyl->color))
		return (NULL);
	cyl->intersect = i_cylinder;
	ft_lstadd_back(&ctx->prims, ft_lstnew(cyl));
	return (tokens);
}
