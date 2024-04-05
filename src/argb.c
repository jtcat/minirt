/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:03:41 by jcat              #+#    #+#             */
/*   Updated: 2024/04/05 01:44:06 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"
#include "utils.h"

static inline int	clamp_uint8(int c)
{
	return (clamp(c, 0, 255));
}

void	write_pix(t_mlx_img *img, int x, int y, t_argb color)
{
	char	*dst;

	dst = img->img_addr + y * img->line_len + x * (img->color_depth / 8);
	*(unsigned int *)dst = color;
}

t_argb	c3_to_argb(t_color3 c)
{
	return ((c.r << (8 * 2)) | (c.g << 8) | c.b);
}

t_color3	c3scalef(t_color3 a, float f)
{
	t_color3	nc;

	nc.r = clamp_uint8(a.r * f);
	nc.g = clamp_uint8(a.g * f);
	nc.b = clamp_uint8(a.b * f);
	return(nc);
}

t_color3	c3sum(t_color3 a, t_color3 b)
{
	return((t_color3){clamp_uint8(a.r + b.r),
			clamp_uint8(a.g + b.g),
			clamp_uint8(a.b + b.b)});
}
