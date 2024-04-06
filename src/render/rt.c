/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:26:57 by jcat              #+#    #+#             */
/*   Updated: 2024/04/06 18:10:19 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/argb.h"
#include "libft.h"
#include <unistd.h>
#include "rt.h"

# define SPEC_EXP 20.f

// Please precalculate full transforms (rot * transl or vice versa)
// They only need to be recalculated when each component is changed
// i.e when the user moves the primitive
void	hit_transform(t_primitive *prim, t_vec3 *hit, t_vec3 *normal)
{
	float	res[4][4];

	mat_mult(prim->transl.mat, prim->rot.mat, res);
	*hit = mat_vec3_mult(res, hit);
	*normal = mat_vec3_mult(prim->rot.mat, normal);
}

// Please precalculate full transforms (rot * transl or vice versa)
void	ray_transform(t_ray *og_ray, t_ray *new_ray, t_primitive *prim)
{
	float	res[4][4];

	mat_mult(prim->rot.inv, prim->transl.inv, res);
	new_ray->origin = mat_vec3_mult(res, &og_ray->origin);
	new_ray->dir = mat_vec3_mult(prim->rot.inv, &og_ray->dir);
}

bool	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *final_hit)
{
	t_list	*iter;
	t_vec2	bound;
	t_hit	tmphit;
	bool	hit_any;
	t_ray	transf_ray;

	hit_any = false;
	iter = ctx->prims;
	bound = (t_vec2){.0001f, INFINITY};
	while (iter)
	{
		ray_transform(ray, &transf_ray, (t_primitive *)iter->content);
		if (((t_primitive *)iter->content)->intersect(((t_primitive *)iter->content)->spec, &transf_ray, bound, &tmphit))
		{
			hit_any = true;
			tmphit.ray = transf_ray;
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

	(void)specular;
	(void)diffuse;
	(void)diffuse_f;
	(void)ray;
	(void)ctx;
	ray.origin = v3sum(hit->ray.origin, v3scalef(v3unit(hit->ray.dir), hit->dist));
	hit_transform(hit->prim, &ray.origin, &hit->normal);
	ray.dir = v3unit(v3sub(mat_getpos(&ctx->light.transl), ray.origin));
	ambient = c3scalef(c3blend(&ctx->ambient, &hit->prim->color, .5f), ctx->ambient_f);
//	if (scene_intersect(ctx, &ray, NULL))
//		//return (c3_to_argb(ambient));
//		return (0);
	hit->normal = v3unit(hit->normal);
	diffuse_f = v3dot(ray.dir, hit->normal) * ctx->light.f;
	diffuse = c3scalef(hit->prim->color, fmax(diffuse_f, 0.f));
//	//specular = c3scalef((t_color3){255, 255, 255}, (diffuse_f > 0) * fmax(pow(v3dot(perf_ray(&ray.dir, &hit->normal),
//			//v3unit(v3sub(hit->ray->origin, ray.origin))), SPEC_EXP), 0.f));
//	//return (c3_to_argb(c3sum(c3sum(ambient,diffuse), specular)));
	return (c3_to_argb(c3sum(ambient,diffuse)));
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
	ft_dprintf(STDOUT_FILENO, "Frame finished\n");
}
