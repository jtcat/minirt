/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:26:57 by jcat              #+#    #+#             */
/*   Updated: 2024/05/03 01:42:26 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../interface/if.h"

static inline t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray)
{
	t_hit	hit;

	if (scene_intersect(ctx, ray, &hit, -1.f) < INFINITY)
		return (get_light_color(ctx, &hit, ray));
	return (0);
}

void	display(t_rtctx *ctx, t_mlx_img *img)
{
	mlx_put_image_to_window(ctx->mlx_ptr,
		ctx->window_ptr, img->img_ptr, 0, 0);
	display_interface(&ctx->ifctx);
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
			ray.origin = ctx->cam.pos;
			ray.dir = v3unit(v3sub(pix_center, ctx->cam.pos));
			write_pix(&ctx->img, x, y, get_ray_color(ctx, &ray));
			x++;
		}
		y++;
	}
}
