/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:39:06 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 09:27:27 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

void	rtctx_init(t_rtctx *ctx)
{
	ctx->cam.hfov = -1;
	ctx->node_n = 0;
	ctx->node_ref_list = NULL;
	ctx->ll_prims = NULL;
	ctx->ll_lights = NULL;
	ctx->ambient.r = -1;
}

void	cleanup_mlx(t_rtctx *ctx)
{
	mlx_destroy_image(ctx->mlx_ptr, ctx->img.img_ptr);
	mlx_destroy_window(ctx->mlx_ptr, ctx->window_ptr);
	mlx_destroy_display(ctx->mlx_ptr);
	free(ctx->mlx_ptr);
}

void	make_node_ref_list(t_rtctx *rtctx)
{
	int		i;
	t_list	*iter;

	rtctx->node_ref_list = malloc(sizeof(t_node3d *) * rtctx->node_n);
	rtctx->node_ref_list[0] = (t_node3d *)&rtctx->cam;
	i = 1;
	iter = rtctx->ll_prims;
	while (iter)
	{
		((t_node3d *)iter->content)->type = NODE_PRIM;
		rtctx->node_ref_list[i++] = iter->content;
		iter = iter->next;
	}
	iter = rtctx->ll_lights;
	while (iter)
	{
		rtctx->node_ref_list[i++] = iter->content;
		iter = iter->next;
	}
}


void	rtctx_destroy(t_rtctx *ctx)
{
	if (ctx->node_ref_list)
		free(ctx->node_ref_list);
	ft_lstclear(&ctx->ll_prims, free);
	ft_lstclear(&ctx->ll_lights, free);
}
