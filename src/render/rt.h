/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:03:30 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 16:57:11 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include "../../minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include <stdbool.h>
# include "../utils.h"
# include "../ray.h"
# include "../datatypes/camera.h"
# include "../datatypes/vec3.h"
# include "../datatypes/argb.h"
# include "../intersect/primitives.h"

# define WINDOW_TITLE "miniRT"
# define DESTROY_NOTIFY 17

# define SPEC_EXP 5.f
# define SPEC_F .8f
# define MIN_HIT_DIST .0001f

typedef struct s_light
{
	t_color3	color;
	t_vec3		pos;
	float		f;
}	t_light;

typedef struct s_rtctx
{
	void		*mlx_ptr;
	void		*window_ptr;
	t_mlx_img	img;
	t_camera	cam;
	t_primitive	*prims;
	t_light		*lights;
	t_list		*ll_lights;
	t_list		*ll_prims;
	int			prim_n;
	int			light_n;
	t_color3	ambient;
	float		ambient_f;
}	t_rtctx;

void	rtctx_init(t_rtctx *ctx);
void	ll_to_arr(t_rtctx *ctx);
void	cleanup_mlx(t_rtctx *ctx);
void	rtctx_destroy(t_rtctx *ctx);
void	render(t_rtctx *ctx);

float	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *hit);
t_argb	get_light_color(t_rtctx *ctx, t_hit *hit);

#endif
