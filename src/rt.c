/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:05:42 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 23:32:08 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "argb.h"
#include "ray.h"
#include "vec3.h"

bool	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *final_hit)
{
	int		i;
	bool	hit_any;
	t_hit	tmp_hit;
	t_vec2	bound;

	i = 0;
	hit_any = false;
	bound = (t_vec2){INFINITY, INFINITY};
	while (i < ctx->prim_n)
	{
		if (ctx->prims[i].intersect(ctx->prims[i].spec, ray, bound, &tmp_hit))
		{
			hit_any = true;
			bound.y = tmp_hit.dist;
			if (final_hit)
				*final_hit = tmp_hit;
		}
		i++;
	}
	return (hit_any);
}

// Each dot product term should only be included if
// its dot product is positive. In addition, the
// specular term should only be included if the
// diffuse dot product is positive
t_argb	get_light_color(t_rtctx *ctx, t_hit *hit)
{
	t_ray	ray;
	t_argb	diffuse;
	t_argb	specular;

	ray.origin = hit->pos;
	ray.dir = v3unit(v3sub(ctx->light.pos, ray.origin));
	hit->normal = v3unit(hit->normal);
	if (scene_intersect(ctx, &ray, NULL))
		return (0);
	diffuse = v3dot(ray.dir, hit->normal);
	specular = diffuse > 0;
	diffuse *= (diffuse > 0 ) * hit->prim->color;
	specular *= v3dot(perf_ray(&ray.dir, &hit->normal),
			v3unit(v3sub(ctx->cam.lookfrom, hit->pos)));
	specular *= (specular > 0) * hit->prim->color;
	return (diffuse + specular);
}

t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray)
{
	t_hit	hit;
	t_argb	color;

	if (scene_intersect(ctx, ray, &hit))
	{
		color = ctx->ambient + get_light_color(ctx, &hit);
		return color;
	}
	return (0);
}

void	render(t_rtctx *ctx)
{
	int		i;
	int		j;
	t_ray	ray;
	t_hit	hit;

	i = 0;
	while (i < ctx->cam.image_height)
	{
		j = 0;
		while (j < ctx->cam.image_width)
		{
			ray.origin = v3sum(v3sum(ctx->cam.pix_ul_p, v3scalei(ctx->cam.pix_du, i)), v3scalei(ctx->cam.pix_dv, j));
			ray.dir = v3sub(ray.origin, ctx->cam.lookfrom);
			write_pix(ctx->img, i, j, get_ray_color(ctx, &ray));
			j++;
		}
		i++;
	}
}
