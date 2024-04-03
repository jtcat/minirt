/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:59:47 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 23:00:50 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGB_H
# define ARGB_H

#include <stdint.h>

typedef union u_argb
{
	int		argb;
	uint8_t	comp[4];
}	t_argb;

typedef struct s_mlx_img {
	char	*img_addr;
	void	*img_ptr;
	int		line_len;
	int		color_depth;
	int		endian;
}	t_mlx_img;

t_argb	rgb(int r, int g, int b);
t_argb 	argbSum(t_argb a, t_argb b);
t_argb 	argbScalef(t_argb a, float f);
void	write_pix(t_mlx_img *img, int x, int y, t_argb color);

#endif
