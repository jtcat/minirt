/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:03:48 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 01:48:19 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"
#include "parser.h"
#include "rt.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include "primitives.h"
#include "vec3.h"

// Top level token parsers like parse_float should
// print their own errors and return false
//
bool	parse_ambient(t_rtctx *ctx, char **tokens)
{
	float	f;
	t_argb	color;

	if (ctx->ambient >= 0.0)
	{
		print_err("Ambient light was redefined");
		return (false);
	}
	if (!parse_float(*(tokens++), f))
		return (false);
	if (f < 0.0f || f > 1.0f)
	{
		print_err("Ambient ratio out of range (0.0 - 1.0)");
		return (false);
	}
	if (!parse_rgb(*(tokens++), &color))
		return (false);
	ctx->ambient = color * f;
	return (true);
}

bool	parse_camera(t_rtctx *ctx, char **tokens)
{
	if (ctx->cam.hfov != -1)
	{
		print_err("Camera was redefined");
		return (false);
	}
	if (!parse_vec3(*(tokens++), &ctx->cam.lookfrom))
		return (false);
	if (!parse_vec3(*(tokens++), &ctx->cam.lookdir) || !is_normal(&ctx->cam.lookdir))
		return (false);
	if (!parse_int(*(tokens++), &ctx->cam.hfov))
		return (false);
	if (ctx->cam.hfov < 0 || ctx->cam.hfov > 180)
	{
		print_err("Camera FOV out of range (0 - 180)");
		return (false);
	}
	return (true);
}

bool parse_light(t_rtctx *ctx, char **tokens)
{
	if (ctx->light.f > 0)
	{
		print_err("Light was redefined");
		return (false);
	}
	if (!parse_vec3(*(tokens++), &ctx->light.pos))
		return (false);
	if (!parse_float(*(tokens++), &ctx->light.f))
		return (false);
	if (ctx->light.f < 0.0f || ctx->light.f > 1.0f)
	{
		print_err("Light intensity out of range (0.0 - 1.0)");
		return (false);
	}
	return (false);
}

bool parse_sphere(t_rtctx *ctx, char **tokens)
{
	t_primitive	*sphere;
	float		radius;
	
	sphere = malloc(sizeof(t_primitive));
	sphere->spec = malloc(sizeof(t_sphere));
	if (!sphere || !sphere->spec)
		return (false);
	if (!parse_vec3(*(tokens++), &((t_sphere *)sphere->spec)->pos))
		return (false);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (false);
	((t_sphere *)sphere->spec)->radius = radius / 2.0f;
	if (!parse_rgb(*(tokens++), &sphere->color))
		return (false);
	sphere->intersect = iSphere;
	ft_lstadd_back(&ctx->prims, ft_lstnew(sphere));
}

bool parse_plane(t_rtctx *ctx, char **tokens)
{
	t_primitive	*plane;
	t_vec3		point;
	t_vec3		normal;
	
	plane = malloc(sizeof(t_primitive));
	plane->spec = malloc(sizeof(t_plane));
	if (!plane || !plane->spec)
		return (false);
	if (!parse_vec3(*(tokens++), &point))
		return (false);
	if (!parse_vec3(*(tokens++), &normal) || !is_normal(&normal))
		return (false);
	if (!parse_rgb(*(tokens++), &plane->color))
		return (false);
	((t_plane *)plane->spec)->height = point;
	((t_plane *)plane->spec)->normal = normal;
	plane->intersect = iPlane;
	ft_lstadd_back(&ctx->prims, ft_lstnew(plane));
}

bool parse_cylinder(t_rtctx *ctx, char **tokens)
{
	t_primitive	*cyl;
	t_vec3		center;
	t_vec3		normal;
	
	cyl = malloc(sizeof(t_primitive));
	cyl->spec = malloc(sizeof(t_cylinder));
	if (!cyl || !cyl->spec)
		return (false);
	if (!parse_vec3(*(tokens++), &((t_cylinder *)cyl->spec)->center))
		return (false);
	if (!parse_vec3(*(tokens++), &normal) || !is_normal(&normal))
		return (false);
	if (!parse_float(*(tokens++), &radius) || radius < 0.0f)
		return (false);
	if (!parse_rgb(*(tokens++), &cyl->color))
		return (false);
	((t_plane *)plane->spec)->height = point;
	((t_plane *)plane->spec)->normal = normal;
	cyl->intersect = iCylinder;
	ft_lstadd_back(&ctx->prims, ft_lstnew(cyl));
}
