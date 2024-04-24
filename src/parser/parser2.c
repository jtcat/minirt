/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:03:48 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 12:13:22 by joaoteix         ###   ########.fr       */
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
#include "../datatypes/light.h"
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
	ctx->node_n++;
	return (tokens);
}

char	**parse_transform(char **tokens, t_node3d *node)
{
	t_vec3	pos;
	t_vec3	dir;

	if (!parse_vec3(*(tokens++), &pos))
		return (NULL);
	if (!parse_vec3(*(tokens++), &dir) || !is_normal(&dir))
		return (NULL);
	tf_look_up(&pos, dir, &node->transf);
	return (tokens);
}

char	**parse_light(t_rtctx *ctx, char **tokens)
{
	t_vec3			pos;
	t_light			*light;

	light = light_new();
	if (!light)
		return (error_helper("Out of memory!"));
	ft_lstadd_back(&ctx->ll_lights, ft_lstnew(light));
	if (!parse_vec3(*(tokens++), &pos))
		return (error_helper("Missing point light position"));
	if (!parse_float(*(tokens++), &light->f))
		return (error_helper("Error in Float"));
	if (light->f < 0.0f || light->f > 1.0f)
		return (error_helper("Light intensity out of range (0.0 - 1.0)"));
	if (!parse_rgb(*(tokens++), &light->color))
		return (error_helper("Missing point light color"));
	tf_from_pos(&pos, &light->node.transf);
	ctx->node_n++;
	return (tokens);
}

char	**parse_sphere(t_rtctx *ctx, char **tokens)
{
	t_sphere	*sphere;
	t_vec3		tmpv;
	float		radius;

	sphere = sphere_new();
	if (!sphere)
		return (error_helper("Out of memory!"));
	ft_lstadd_back(&ctx->ll_prims, ft_lstnew(sphere));
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	tf_from_pos(&tmpv, &((t_node3d *)sphere)->transf);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (NULL);
	sphere->r = radius / 2.0f;
	if (!parse_rgb(*(tokens++), &((t_primitive *)sphere)->color))
		return (NULL);
	ctx->node_n++;
	return (tokens);
}
