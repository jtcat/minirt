/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:03:41 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 21:21:15 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"

void	write_pix(t_mlx_img *img, int x, int y, t_argb color)
{
	char	*dst;

	dst = img->img_addr + y * img->line_len + x * (img->color_depth / 8);
	*(unsigned int *)dst = color;
}
