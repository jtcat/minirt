/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:03:30 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 02:56:32 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include "ray.h"
# include "argb.h"
# include "camera.h"
# include "vec3.h"
# include "vec2.h"
# include "primitives.h"

typedef struct s_light {
	t_vec3	pos;
	float	f;
}	t_light;

typedef struct s_rtctx {
	t_mlx_img	*img;
	t_camera	cam;
	t_list		*prims;
	int			prim_n;
	t_light		light;
	t_argb		ambient;
}	t_rtctx;

void	rtctx_init(t_rtctx *ctx);
void	render(t_rtctx *ctx);
void	exit_err(t_rtctx *ctx, char *msg);
void	rtctx_destroy(t_rtctx *ctx);
bool	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *final_hit);
t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray);
void	ray_prim_transform(t_ray *ray, t_primitive *primitive);

#endif
