/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:36:04 by joaoteix          #+#    #+#             */
/*   Updated: 2024/02/03 19:05:12 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_argb	calc_color(t_rtctx *ctx, t_hit *hit)
{
	int		i;
	double	brightness;

	i = 0;
	while (i < ctx->light_n)
	{
		
		i++;
	}
}

t_argb	trace(t_rtctx *ctx, vec3 ro, vec3 rd)
{
	int		i;
	t_hit	closest;
	t_hit	tmphit;

	i = 0;
	closest.dist = 0;
	while (i < rtctx->prim_n)
	{
		intersect(rtctx->primlist[i], &tmphit, ro, rd);
		if (tmphit.dist < closest.dist)
			closest = tmphit;
		i++;
	}
	calc_color(ctx, &closest);
}

{
	char	*image_dst;

	dst = ctx->img_addr + y * ctx->line_len + x * (ctx->color_depth / 8);
	*(unsigned int *)dst = closest.color;
}
