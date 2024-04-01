/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:39:06 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 01:57:44 by jcat             ###   ########.fr       */
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
	ctx->prims = NULL;
	ctx->prim_n = 0;
	ctx->ambient = -1.0f;
	ctx->cam.hfov = -1;
}

void	rtctx_destroy(t_rtctx *ctx)
{
	ft_lstclear(&ctx->prims, prim_destroy);
}
