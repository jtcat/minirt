/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:18:46 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 21:25:08 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	norm_calc(t_hit *hit)
{
	hit->norm_fn(hit);
	hit->normal = transf_vec(hit->prim->transf.mat, &hit->normal);
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
	t_hit	tmp_hit;
	float	tmp_dist;

	i = 0;
	tmp_hit.bound.y = INFINITY;
	tmp_hit.bound.x = MIN_HIT_DIST;
	while (i < ctx->prim_n)
	{
		ray_transform(ray, &tmp_hit.ray, &ctx->prims[i]);
		tmp_dist = ctx->prims[i].intersect(ctx->prims[i].spec, &tmp_hit);
		if (tmp_dist > MIN_HIT_DIST)
		{
			tmp_hit.bound.y = tmp_dist;
			tmp_hit.prim = &ctx->prims[i];
			*hit = tmp_hit;
		}
		i++;
	}
	return (tmp_hit.bound.y);
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

	i = -1;
	color = c3prod(hit->prim->color, ctx->ambient);
	while (++i < ctx->light_n)
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
	}
	return (color);
}

t_argb	get_light_color(t_rtctx *ctx, t_hit *hit)
{
	t_ray	ray;

	norm_calc(hit);
	ray.origin = v3sum(hit->ray.origin,
			v3scalef(v3unit(hit->ray.dir), hit->bound.y * 0.999f));
	ray.origin = transf_point(hit->prim->transf.mat, &ray.origin);
	return (c3_to_argb(light_cast(ctx, &ray, hit)));
}
