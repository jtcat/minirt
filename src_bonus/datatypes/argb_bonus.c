/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:03:41 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 14:00:35 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb_bonus.h"
#include "../utils_bonus.h"

static inline double	normalize_f(double f)
{
	return (fclamp(f, 0.f, 1.f));
}

void	write_pix(t_mlx_img *img, int x, int y, t_argb color)
{
	char	*dst;

	dst = img->img_addr + y * img->line_len + x * (img->color_depth / 8);
	*(unsigned int *)dst = color;
}

t_argb	c3_to_argb(t_color3 c)
{
	return (((int)(c.r * 255.f) << 16)
			| ((int)(c.g * 255.f) << 8)
			| (int)(c.b * 255.f));
}

t_color3	c3scalef(t_color3 a, float f)
{
	return ((t_color3){normalize_f(a.r * f),
		normalize_f(a.g * f),
		normalize_f(a.b * f)});
}

t_color3	c3sum(t_color3 a, t_color3 b)
{
	return ((t_color3){normalize_f(a.r + b.r),
		normalize_f(a.g + b.g),
		normalize_f(a.b + b.b)});
}
