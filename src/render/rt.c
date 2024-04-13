/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:18:46 by jcat              #+#    #+#             */
/*   Updated: 2024/04/14 00:32:28 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define SPEC_EXP 5.f
#define SPEC_F .8f
#define MIN_HIT_DIST .0001f

static inline void	hit_transform(
		t_primitive *prim, t_vec3 *hit, t_vec3 *normal)
{
	*hit = transf_point(prim->transf.mat, hit);
	*normal = transf_vec(prim->transf.mat, normal);
}

static inline void	ray_transform(
		t_ray *og_ray, t_ray *new_ray, t_primitive *prim)
{
	new_ray->origin = transf_point(prim->transf.inv, &og_ray->origin);
	new_ray->dir = transf_vec(prim->transf.inv, &og_ray->dir);
}

float	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *hit)
{
	int		i;
	t_vec2	bound;
	t_ray	transf_ray;

	i = 0;
	bound = (t_vec2){MIN_HIT_DIST, INFINITY};
	hit->dist = INFINITY;
	while (i < ctx->prim_n)
	{
		ray_transform(ray, &transf_ray, &ctx->prims[i]);
		if (ctx->prims[i].intersect(ctx->prims[i].spec,
				&transf_ray, bound, hit))
		{
			hit->ray = transf_ray;
			hit->prim = &ctx->prims[i];
			bound.y = hit->dist;
		}
		i++;
	}
	return (hit->dist);
}

// Each dot product term should only be included if
// its dot product is positive. In addition, the
// specular term should only be included if the
// diffuse dot product is positive
//
// specular term is -dot to negate ray dir
static inline t_color3	light_cast(t_rtctx *ctx, t_ray *ray, t_hit *hit)
{
	int			i;
	float		diffuse_f;
	t_hit		pass;
	t_vec3		surf_to_light;
	t_color3	color;

	i = 0;
	color = c3prod(hit->prim->color, ctx->ambient);
	while (i < ctx->light_n)
	{
		surf_to_light = v3sub(ctx->lights[i].pos, ray->origin);
		ray->dir = v3unit(surf_to_light);
		if (scene_intersect(ctx, ray, &pass) < v3length(&surf_to_light))
			return (color);
		diffuse_f = fmax(v3dot(ray->dir, hit->normal)
				* ctx->lights[i].f, 0.f);
		color = c3sum(color, c3prod(c3scalef(ctx->lights[i].color,
						diffuse_f), hit->prim->color));
		color = c3sum(color, c3scalef((t_color3){1.f, 1.f, 1.f},
					(diffuse_f >= 0.f) * pow(fmax(-v3dot(perf_ray(&ray->dir,
									&hit->normal), hit->ray.dir), 0.f)
						* SPEC_F, SPEC_EXP)));
		i++;
	}
	return (color);
}

t_argb	get_light_color(t_rtctx *ctx, t_hit *hit)
{
	t_ray	ray;

	hit->normal = v3unit(hit->normal);
	ray.origin = v3sum(hit->ray.origin,
			v3scalef(v3unit(hit->ray.dir), hit->dist * 0.999f));
	hit_transform(hit->prim, &ray.origin, &hit->normal);
	return (c3_to_argb(light_cast(ctx, &ray, hit)));
}
