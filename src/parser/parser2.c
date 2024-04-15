/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:03:48 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 17:09:37 by jcat             ###   ########.fr       */
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

// Top level token parsers like parse_float should
// print their own errors and return NULL

char	**parse_ambient(t_rtctx *ctx, char **tokens)
{
	if (ctx->ambient.r > -1)
		return (error_helper("Ambient light was redefined"));
	if (!parse_float(*(tokens++), &ctx->ambient_f))
		return (error_helper("Malformed Floar"));
	if (ctx->ambient_f < 0.0f || ctx->ambient_f > 1.0f)
		return (error_helper("Ambient ratio out of range (0.0 - 1.0)"));
	if (!parse_rgb(*(tokens++), &ctx->ambient))
		return (error_helper("Malformed RGB"));
	ctx->ambient = c3scalef(ctx->ambient, ctx->ambient_f);
	return (tokens);
}

char	**parse_camera(t_rtctx *ctx, char **tokens)
{
	int	fov;

	if (ctx->cam.hfov > -1.0)
		return (error_helper("Camera was redefined"));
	if (!parse_vec3(*(tokens++), &ctx->cam.lookfrom))
		return (error_helper("Camera position error"));
	if (!parse_vec3(*(tokens++), &ctx->cam.lookdir)
		|| !is_normal(&ctx->cam.lookdir))
		return (error_helper("Camera direction error"));
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
	tf_look_up(&pos, dir, t);
	return (tokens);
}

char	**parse_light(t_rtctx *ctx, char **tokens)
{
	t_light			*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	ft_lstadd_back(&ctx->ll_lights, ft_lstnew(light));
	if (!parse_vec3(*(tokens++), &light->pos))
		return (error_helper("Missing point light position"));
	if (!parse_float(*(tokens++), &light->f))
		return (error_helper("Error in Float"));
	if (light->f < 0.0f || light->f > 1.0f)
		return (error_helper("Light intensity out of range (0.0 - 1.0)"));
	if (!parse_rgb(*(tokens++), &light->color))
		return (error_helper("Missing point light color"));
	++ctx->light_n;
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
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(sphere));
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	tf_from_pos(&tmpv, &sphere->transf);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (NULL);
	((t_sphere *)sphere->spec)->radius = radius / 2.0f;
	if (!parse_rgb(*(tokens++), &sphere->color))
		return (NULL);
	sphere->intersect = i_sphere;
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
