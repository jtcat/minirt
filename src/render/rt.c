/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:18:46 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 10:35:54 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../datatypes/light.h"

static inline void	norm_calc(t_hit *hit)
{
	hit->norm_fn(hit);
	hit->normal = transf_vec(hit->prim->node.transf.mat, &hit->normal);
}

static inline void	ray_transform(
		t_ray *og_ray, t_ray *new_ray, t_primitive *prim)
{
	new_ray->origin = transf_point(prim->node.transf.inv, &og_ray->origin);
	new_ray->dir = transf_vec(prim->node.transf.inv, &og_ray->dir);
}

float	scene_intersect(t_rtctx *rtctx, t_ray *ray, t_hit *hit)
{
	t_primitive	*prim;
	t_list		*node;
	t_hit		tmp_hit;
	float		tmp_dist;

	tmp_hit.bound.y = INFINITY;
	tmp_hit.bound.x = MIN_HIT_DIST;
	node = rtctx->ll_prims;
	while (node)
	{
		prim = ((t_primitive *)node->content);
		ray_transform(ray, &tmp_hit.ray, prim);
		tmp_dist = prim->intersect(prim, &tmp_hit);
		if (tmp_dist > MIN_HIT_DIST)
		{
			tmp_hit.bound.y = tmp_dist;
			tmp_hit.prim = prim;
			if (hit)
				*hit = tmp_hit;
		}
		node = node->next;
	}
	return (tmp_hit.bound.y);
}

// Each dot product term should only be included if
// its dot product is positive. In addition, the
// specular term should only be included if the
// diffuse dot product is positive
//
// specular term is -dot to negate ray dir
static inline t_color3	light_cast(t_rtctx *rtctx, t_ray *ray, t_hit *hit)
{
	t_list		*node;
	t_light		*light;
	float		diffuse_f;
	t_color3	color;

	node = rtctx->ll_lights;
	color = c3prod(hit->prim->color, rtctx->ambient);
	while (node)
	{
		light = (t_light *)node->content;
		ray->dir = v3unit(v3sub(tf_get_pos(&light->node.transf), ray->origin));
		if (scene_intersect(rtctx, ray, NULL) >= v3length(&ray->dir))
		{
			diffuse_f = fmax(v3dot(ray->dir, hit->normal) * light->f, 0.f);
			color = c3sum(color, c3prod(c3scalef(light->color,
							diffuse_f), hit->prim->color));
			color = c3sum(color, c3scalef((t_color3){1.f, 1.f, 1.f},
						(diffuse_f >= 0.f) * pow(fmax(-v3dot(perf_ray(&ray->dir,
										&hit->normal), hit->ray.dir), 0.f)
							* SPEC_F, SPEC_EXP)));
		}
		node = node->next;
	}
	return (color);
}

t_argb	get_light_color(t_rtctx *rtctx, t_hit *hit)
{
	t_ray	ray;

	norm_calc(hit);
	ray.origin = v3sum(hit->ray.origin,
			v3scalef(v3unit(hit->ray.dir), hit->bound.y * 0.999f));
	ray.origin = transf_point(hit->prim->node.transf.mat, &ray.origin);
	return (c3_to_argb(light_cast(rtctx, &ray, hit)));
}
