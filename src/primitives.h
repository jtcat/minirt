/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:14 by jcat              #+#    #+#             */
/*   Updated: 2024/04/03 17:13:23 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "matrix.h"
# include "vec3.h"
# include "vec2.h"
# include "ray.h"
# include "argb.h"
# include "utils.h"
# include <stdlib.h>
# include <stdbool.h>

enum e_primtype {PRIM_PLANE, PRIM_SPHERE, PRIM_CYLINDER};

typedef struct s_primitive t_primitive;

typedef struct s_hit {
	t_primitive	*prim;
	t_vec3		pos;
	t_vec3		normal;
	double		dist;
}	t_hit;

typedef bool	(*t_fn_intersect)(t_primitive *prim, t_ray *ray, t_vec2 bound, t_hit *hit);

typedef struct s_primitive {
	enum e_primtype	type;
	t_transf		transl;
	t_transf		rot;
	t_argb			color;
	void			*spec;
	t_fn_intersect	intersect;
}	t_primitive;


typedef struct s_sphere
{
	float	radius;
}	t_sphere;

typedef struct s_cylinder
{
	float	radius;
	float	height;
}	t_cylinder;

void	prim_init(t_primitive *prim);
void	prim_destroy(void *vprim);

// Intersections
bool	i_sphere(t_primitive *prim, t_ray *ray, t_vec2 bound, t_hit *hit);
bool	i_plane(t_primitive *prim, t_ray *ray, t_vec2 distBound, t_hit *hit);
bool	i_cylinder(t_primitive *prim, t_ray *ray, t_vec2 bound, t_hit *hit);
#endif
