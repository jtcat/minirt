/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:39:06 by jcat              #+#    #+#             */
/*   Updated: 2024/04/13 16:20:48 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	ctx->prim_n = 0;
	ctx->light_n = 0;
	ctx->ll_prims = NULL;
	ctx->ll_lights = NULL;
	ctx->prims = NULL;
	ctx->lights = NULL;
	ctx->ambient.r = -1;
}

void	cleanup_mlx(t_rtctx *ctx)
{
	mlx_destroy_image(ctx->mlx_ptr, ctx->img.img_ptr);
	mlx_destroy_window(ctx->mlx_ptr, ctx->window_ptr);
	mlx_destroy_display(ctx->mlx_ptr);
	free(ctx->mlx_ptr);
}

void	ll_to_arr(t_rtctx *ctx)
{
	t_list	*iter;
	int		i;

	ctx->lights = malloc(sizeof(t_light) * ctx->light_n);
	ctx->prims = malloc(sizeof(t_primitive) * ctx->prim_n);
	iter = ctx->ll_lights;
	i = 0;
	while (iter)
	{
		ctx->lights[i++] = *(t_light *)iter->content;
		iter = iter->next;
	}
	iter = ctx->ll_prims;
	i = 0;
	while (iter)
	{
		ctx->prims[i++] = *(t_primitive *)iter->content;
		iter = iter->next;
	}
	ft_lstclear(&ctx->ll_lights, free);
	ft_lstclear(&ctx->ll_prims, free);
	ctx->ll_lights = NULL;
	ctx->ll_prims = NULL;
}

void	rtctx_destroy(t_rtctx *ctx)
{
	ft_lstclear(&ctx->ll_lights, free);
	ft_lstclear(&ctx->ll_prims, free);
	if (ctx->prims)
	{
		while (ctx->prim_n--)
			free(ctx->prims[ctx->prim_n].spec);
		free(ctx->prims);
	}
	if (ctx->lights)
		free(ctx->lights);
}
