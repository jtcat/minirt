/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:03:30 by jcat              #+#    #+#             */
/*   Updated: 2024/05/03 01:42:13 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include "../../minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include <stdbool.h>
# include "../utils.h"
# include "../datatypes/ray.h"
# include "../datatypes/camera.h"
# include "../datatypes/argb.h"
# include "../intersect/primitives.h"
# include "../interface/if_utils.h"

# define WINDOW_TITLE "miniRT"
# define DESTROY_NOTIFY 17

# define SPEC_EXP 5.f
# define SPEC_F .8f
# define MIN_HIT_DIST .0001f

# define IF_MODE_FIRST IF_MODE_TRANSLATE
# define IF_MODE_LAST IF_MODE_MORPH

typedef struct s_rtctx
{
	t_ifctx		ifctx;
	void		*mlx_ptr;
	void		*window_ptr;
	t_mlx_img	img;
	t_camera	cam;
	t_node3d	**node_ref_list;
	t_list		*ll_prims;
	t_list		*ll_lights;
	int			node_n;
	t_color3	ambient;
	float		ambient_f;
}	t_rtctx;

void	rtctx_init(t_rtctx *ctx);
void	make_obj_list(t_rtctx *ctx);
void	cleanup_mlx(t_rtctx *ctx);
void	rtctx_destroy(t_rtctx *ctx);
void	make_node_ref_list(t_rtctx *rtctx);

int		key_handler(int keycode, t_rtctx *params);

void	display(t_rtctx *ctx, t_mlx_img *img);
void	render(t_rtctx *ctx);
float	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *hit, float min_cull_dist);
t_argb	get_light_color(t_rtctx *rtctx, t_hit *hit, t_ray *og_ray);

#endif
