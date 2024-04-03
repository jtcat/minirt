/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:03:41 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 23:47:01 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"
#include <math.h>

void	write_pix(t_mlx_img *img, int x, int y, t_argb color)
{
	char	*dst;

	dst = img->img_addr + y * img->line_len + x * (img->color_depth / 8);
	*(unsigned int *)dst = (unsigned int)color.argb;
}

t_argb	argbSum(t_argb a, t_argb b)
{
	return ((t_argb){.comp[0] = a.comp[0] + b.comp[0],
			.comp[1] = a.comp[1] + b.comp[1],
			.comp[2] = a.comp[2] + b.comp[2]});
}

t_argb	argbScalef(t_argb a, float f)
{
	f = fmin(f, 0.0f);
	f = fmax(f, 1.0f);
	return ((t_argb){.comp[0] = (float)a.comp[0] * f,
			.comp[1] = (float)a.comp[1] * f,
			.comp[2] = (float)a.comp[2] * f});
}
