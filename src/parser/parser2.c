/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:03:48 by jcat              #+#    #+#             */
/*   Updated: 2024/04/07 02:25:32 by jcat             ###   ########.fr       */
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
	{
		print_err("Ambient light was redefined");
		return (NULL);
	}
	if (!parse_float(*(tokens++), &ctx->ambient_f))
		return (NULL);
	if (ctx->ambient_f < 0.0f || ctx->ambient_f > 1.0f)
	{
		print_err("Ambient ratio out of range (0.0 - 1.0)");
		return (NULL);
	}
	if (!parse_rgb(*(tokens++), &ctx->ambient))
		return (NULL);
	return (tokens);
}

char	**parse_camera(t_rtctx *ctx, char **tokens)
{
	int	fov;

	if (ctx->cam.hfov > -1.0)
	{
		print_err("Camera was redefined");
		return (NULL);
	}
	if (!parse_vec3(*(tokens++), &ctx->cam.lookfrom))
		return (NULL);
	if (!parse_vec3(*(tokens++), &ctx->cam.lookdir) || !is_normal(&ctx->cam.lookdir))
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

char	**parse_light(t_rtctx *ctx, char **tokens)
{
	t_vec3	tmpv;

	if (ctx->light.f > 0)
	{
		print_err("Light was redefined");
		return (NULL);
	}
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	transf_from_v3(&tmpv, &ctx->light.transl);
	if (!parse_float(*(tokens++), &ctx->light.f))
		return (NULL);
	if (ctx->light.f < 0.0f || ctx->light.f > 1.0f)
	{
		print_err("Light intensity out of range (0.0 - 1.0)");
		return (NULL);
	}
	if (!parse_rgb(*(tokens++), &ctx->light.color))
		return (NULL);
	return (tokens);
}

char	**parse_sphere(t_rtctx *ctx, char **tokens)
{
	t_primitive	*sphere;
	float		radius;
	t_vec3		tmpv;
	
	sphere = malloc(sizeof(t_primitive));
	sphere->spec = malloc(sizeof(t_sphere));
	if (!sphere || !sphere->spec)
		return (NULL);
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	transf_from_v3(&tmpv, &sphere->transf);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (NULL);
	((t_sphere *)sphere->spec)->radius = radius / 2.0f;
	if (!parse_rgb(*(tokens++), &sphere->color))
		return (NULL);
	tmpv = (t_vec3){0, 1.0, 0};
	rot_from_up(&tmpv, &sphere->transf);
	sphere->intersect = i_sphere;
	ft_lstadd_back(&ctx->prims, ft_lstnew(sphere));
	return (tokens);
}

char	**parse_plane(t_rtctx *ctx, char **tokens)
{
	t_primitive	*plane;
	t_vec3		tmpv;
	
	plane = malloc(sizeof(t_primitive));
	plane->spec = NULL;
	if (!plane)
		return (NULL);
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	transf_from_v3(&tmpv, &plane->transf);
	if (!parse_vec3(*(tokens++), &tmpv) || !is_normal(&tmpv))
		return (NULL);
	rot_from_up(&tmpv, &plane->transf);
	if (!parse_rgb(*(tokens++), &plane->color))
		return (NULL);
	plane->intersect = i_plane;
	ft_lstadd_back(&ctx->prims, ft_lstnew(plane));
	return (tokens);
}

char	**parse_cylinder(t_rtctx *ctx, char **tokens)
{
	t_primitive	*cyl;
	t_vec3		tmpv;
	float		tmp;
	
	cyl = malloc(sizeof(t_primitive));
	cyl->spec = malloc(sizeof(t_cylinder));
	if (!cyl || !cyl->spec)
		return (NULL);
	if (!parse_vec3(*(tokens++), &tmpv))
		return (NULL);
	transf_from_v3(&tmpv, &cyl->transf);
	if (!parse_vec3(*(tokens++), &tmpv) || !is_normal(&tmpv))
		return (NULL);
	rot_from_up(&tmpv, &cyl->transf);
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->radius = tmp / 2.0;
	if (!parse_float(*(tokens++), &tmp) || tmp < 0.0f)
		return (NULL);
	((t_cylinder *)cyl->spec)->height = tmp;
	if (!parse_rgb(*(tokens++), &cyl->color))
		return (NULL);
	cyl->intersect = i_cylinder;
	ft_lstadd_back(&ctx->prims, ft_lstnew(cyl));
	return (tokens);
}
