/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:03:30 by jcat              #+#    #+#             */
/*   Updated: 2024/04/06 23:20:52 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include "../../minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include <stdlib.h>
# include <stdbool.h>
# include "../utils.h"
# include "../ray.h"
# include "../datatypes/camera.h"
# include "../datatypes/vec3.h"
# include "../datatypes/vec2.h"
# include "../datatypes/matrix.h"
# include "../datatypes/argb.h"
# include "../intersect/primitives.h"

# define WINDOW_TITLE "miniRT"
# define DESTROY_NOTIFY 17

typedef struct s_light {
	t_color3	color;
	t_transf	transl;
	float		f;
}	t_light;

typedef struct s_rtctx {
	void		*mlx_ptr;
	void		*window_ptr;
	t_mlx_img	img;
	t_camera	cam;
	t_list		*prims;
	int			prim_n;
	t_light		light;
	t_color3	ambient;
	float		ambient_f;
}	t_rtctx;

void	rtctx_init(t_rtctx *ctx);
void	render(t_rtctx *ctx);
void	exit_err(t_rtctx *ctx, char *msg);
void	rtctx_destroy(t_rtctx *ctx);
void	cleanup_mlx(t_rtctx *ctx);
void	ray_prim_transform(t_ray *ray, t_primitive *primitive);

#endif
