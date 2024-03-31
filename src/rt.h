/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:03:30 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 23:48:06 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include "ray.h"
#include "argb.h"
#include "camera.h"
#include "vec3.h"
#include "vec2.h"

enum e_primtype {PRIM_PLANE, PRIM_SPHERE, PRIM_CYLINDER};

typedef struct s_primitive t_primitive;

typedef struct s_hit {
	t_primitive	*prim;
	t_vec3		pos;
	t_vec3		normal;
	double		dist;
}	t_hit;

typedef bool	(*t_fnIntersect)(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit);

typedef struct s_primitive {
	enum e_primtype	type;
	t_argb			color;
	void			*spec;
	t_fnIntersect	intersect;
	// primitive methods
	// intersect
	// transform
	// respec
}	t_primitive;

typedef struct s_light {
	t_vec3	pos;
	t_argb	color;
}	t_light;

typedef struct s_rtctx {
	t_mlx_img	*img;
	t_camera	cam;
	t_primitive	*prims;
	int			prim_n;
	t_light		light;
	t_argb		ambient;
}	t_rtctx;

void	render(t_rtctx *ctx);
void	exit_err(t_rtctx *ctx, char *msg);
void	rtctx_destroy(t_rtctx *ctx);
bool	scene_intersect(t_rtctx *ctx, t_ray *ray, t_hit *final_hit);
t_argb	get_ray_color(t_rtctx *ctx, t_ray *ray);

#endif
