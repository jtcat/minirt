/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:59:47 by jcat              #+#    #+#             */
/*   Updated: 2024/04/18 16:13:28 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGB_H
# define ARGB_H

# include <stdint.h>

typedef struct s_color3
{
	float	r;
	float	g;
	float	b;
}	t_color3;

typedef int	t_argb;

typedef struct s_mlx_img
{
	char	*img_addr;
	void	*img_ptr;
	int		line_len;
	int		color_depth;
	int		endian;
}	t_mlx_img;

t_argb		c3_to_argb(t_color3 c);
t_color3	color3(float r, float g, float b);
t_color3	c3sum(t_color3 a, t_color3 b);
t_color3	c3prod(t_color3 a, t_color3 b);
t_color3	c3scalef(t_color3 a, float f);
void		write_pix(t_mlx_img *img, int x, int y, t_argb color);

#endif
