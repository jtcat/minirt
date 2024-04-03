/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:39:06 by jcat              #+#    #+#             */
/*   Updated: 2024/04/04 00:23:23 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	exit_err(t_rtctx *ctx, char *msg)
{
	rtctx_destroy(ctx);
	print_err(msg);
	exit(1);
}

void	rtctx_init(t_rtctx *ctx)
{
	ctx->cam.hfov = -1;
	ctx->light.f = -1;
	ctx->prims = NULL;
	ctx->prim_n = 0;
	ctx->ambient.argb = -1;
}

void	cleanup_mlx(t_rtctx *ctx)
{
	mlx_destroy_image(ctx->mlx_ptr, ctx->img.img_ptr);
	mlx_destroy_window(ctx->mlx_ptr, ctx->window_ptr);
	mlx_destroy_display(ctx->mlx_ptr);
	free(ctx->mlx_ptr);
}

void	rtctx_destroy(t_rtctx *ctx)
{
	ft_lstclear(&ctx->prims, prim_destroy);
}
