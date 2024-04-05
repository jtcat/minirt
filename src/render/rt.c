/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:26:57 by jcat              #+#    #+#             */
/*   Updated: 2024/04/05 12:19:16 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/argb.h"
#include "rt.h"

# define SPEC_EXP 6.f

void	hit_transform(t_hit *hit)
{
	float	res[4][4];

	mat_mult(hit->prim->transl.mat, hit->prim->rot.mat, res);
	//hit->pos = mat_vec3_mult(res, &hit->pos);
	hit->normal = mat_vec3_mult(hit->prim->rot.mat, &hit->normal);
}

void	ray_prim_transform(t_ray *ray, t_primitive *prim)
{
	float	res[4][4];

	mat_mult(prim->rot.inv, prim->transl.inv, res);
	ray->origin = mat_vec3_mult(res, &ray->origin);
	ray->dir = mat_vec3_mult(prim->rot.inv, &ray->dir);
}

bool	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *final_hit)
{
	t_list	*iter;
	t_vec2	bound;
	t_hit	tmphit;
	bool	hit_any;

	hit_any = false;
	iter = ctx->prims;
	bound = (t_vec2){.0001f, INFINITY};
	while (iter)
	{
		//ray_prim_transform(ray, (t_primitive *)iter->content);
		if (((t_primitive *)iter->content)->intersect(iter->content, ray, bound, &tmphit))
		{
			hit_any = true;
			tmphit.ray = ray;
			bound.y = tmphit.dist;
			tmphit.prim = iter->content;
		}
		iter = iter->next;
	}
	if (final_hit)
		*final_hit = tmphit;
	return (hit_any);
}

static inline t_color3	c3blend(t_color3 *a, t_color3 *b, float f)
{
	return (c3sum(c3scalef(*a, f), c3scalef(*b, 1.f - f)));
}

// Each dot product term should only be included if
// its dot product is positive. In addition, the
// specular term should only be included if the
// diffuse dot product is positive
t_argb	get_light_color(t_rtctx *ctx, t_hit *hit)
{
	t_ray		ray;
	float		diffuse_f;
	t_color3	diffuse;
	t_color3	ambient;
	t_color3	specular;

	(void)ambient;
	(void)diffuse;
	(void)specular;
	//hit_transform(hit);
	ray.origin = v3sum(hit->ray->origin, v3scalef(v3unit(hit->ray->dir), hit->dist));
	ray.dir = v3unit(v3sub(mat_getpos(&ctx->light.transl), ray.origin));
	hit->normal = v3unit(hit->normal);
	ambient = c3scalef(c3blend(&ctx->ambient, &hit->prim->color, ctx->ambient_f), ctx->ambient_f);
	if (scene_intersect(ctx, &ray, NULL))
		return (c3_to_argb(c3scalef(ambient, ctx->ambient_f)));
	diffuse_f = v3dot(ray.dir, hit->normal);
	diffuse = c3scalef(hit->prim->color, fmax(diffuse_f, 0.f));
	specular = c3scalef((t_color3){255, 255, 255}, (float)(diffuse_f > 0.f) * fmax(pow(v3dot(perf_ray(&ray.dir, &hit->normal),
			v3unit(v3sub(hit->ray->origin, ray.origin))), SPEC_EXP), 0.f));
	return (c3_to_argb(c3sum(specular, c3blend(&ambient,&diffuse, ctx->ambient_f))));
}

t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray)
{
	t_hit	hit;

	if (scene_intersect(ctx, ray, &hit))
		return (get_light_color(ctx, &hit));
	return (0);
}

void	render(t_rtctx *ctx)
{
	int		y;
	int		x;
	t_ray	ray;
	t_vec3	pix_center;

	y = 0;
	while (y < ctx->cam.image_height)
	{
		x = 0;
		while (x < ctx->cam.image_width)
		{
			pix_center = v3sum(v3sum(ctx->cam.pix_ul_p, v3scalei(ctx->cam.pix_du, x)), v3scalei(ctx->cam.pix_dv, y));
			ray.origin = ctx->cam.lookfrom;
			ray.dir = v3sub(pix_center, ctx->cam.lookfrom);
			write_pix(&ctx->img, x, y, get_ray_color(ctx, &ray));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(ctx->mlx_ptr, ctx->window_ptr, ctx->img.img_ptr, 0, 0);
}
