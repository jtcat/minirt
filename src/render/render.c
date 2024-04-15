/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:26:57 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 16:59:32 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray)
{
	t_hit	hit;

	if (scene_intersect(ctx, ray, &hit) < INFINITY)
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
			pix_center = v3sum(v3sum(ctx->cam.pix_ul_p,
						v3scalei(ctx->cam.pix_du, x)),
					v3scalei(ctx->cam.pix_dv, y));
			ray.origin = ctx->cam.lookfrom;
			ray.dir = v3unit(v3sub(pix_center, ctx->cam.lookfrom));
			write_pix(&ctx->img, x, y, get_ray_color(ctx, &ray));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(ctx->mlx_ptr,
		ctx->window_ptr, ctx->img.img_ptr, 0, 0);
}
