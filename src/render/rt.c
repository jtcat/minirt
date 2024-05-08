/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:18:46 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 15:14:14 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../datatypes/light.h"

static inline void	ray_transform(
		t_ray *og_ray, t_ray *new_ray, t_primitive *prim)
{
	new_ray->origin = transf_point(prim->node.transf.inv, &og_ray->origin);
	new_ray->dir = transf_vec(prim->node.transf.inv, &og_ray->dir);
}

double	scene_intersect(t_rtctx *rtctx, t_ray *ray,
		t_hit *hit, double min_cull_dist)
{
	t_primitive	*prim;
	t_list		*node;
	t_hit		tmp_hit;
	double		tmp_dist;

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
			if (tmp_dist < min_cull_dist)
				return (-1.f);
			tmp_hit.bound.y = tmp_dist;
			tmp_hit.prim = prim;
			if (hit)
				*hit = tmp_hit;
		}
		node = node->next;
	}
	return (tmp_hit.bound.y);
}

float	spec_f(t_ray *ray, t_hit *hit, t_ray *og_ray)
{
	return (pow(fmax(-v3dot(perf_ray(&ray->dir,
						&hit->normal), og_ray->dir), 0.f) * SPEC_F, SPEC_EXP));
}

// Each dot product term should only be included if
// its dot product is positive. In addition, the
// specular term should only be included if the
// diffuse dot product is positive
//
// specular term is -dot to negate ray dir
t_color3	light_cast(t_rtctx *rtctx, t_ray *ray, t_hit *hit)
{
	t_list		*node;
	t_light		*light;
	float		diffuse_f;
	t_vec3		light_vec;
	t_color3	color;

	node = rtctx->ll_lights;
	color = c3prod(hit->prim->color, rtctx->ambient);
	while (node)
	{
		light = (t_light *)node->content;
		light_vec = v3sub(tf_get_vec(&light->node.transf, 3), ray->origin);
		ray->dir = v3unit(light_vec);
		if (scene_intersect(rtctx, ray, NULL,
				v3length(&light_vec) * .999) > -1.f)
		{
			diffuse_f = fmax(v3dot(ray->dir, hit->normal) * light->f, 0.f);
			color = c3sum(color, c3prod(c3scalef(light->color, diffuse_f),
						hit->prim->color));
		}
		node = node->next;
	}
	return (color);
}
