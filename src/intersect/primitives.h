/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:14 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 17:11:18 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "../datatypes/matrix.h"
# include "../datatypes/vec3.h"
# include "../datatypes/vec2.h"
# include "../datatypes/argb.h"
# include "../utils.h"
# include "../ray.h"
# include <stdlib.h>
# include <stdbool.h>

enum e_primtype
{
	PRIM_PLANE,
	PRIM_SPHERE,
	PRIM_CYLINDER
};

typedef struct s_primitive	t_primitive;
typedef struct s_hit	t_hit;

typedef void(*t_fn_norm)(t_hit *hit);
typedef float(*t_fn_intersect)(void *prim, t_hit *hit);

struct s_hit
{
	t_primitive	*prim;
	t_ray		ray;
	t_vec3		normal;
	t_vec2		bound;
	t_fn_norm	norm_fn;
};

struct s_primitive
{
	enum e_primtype	type;
	t_transf		transf;
	t_color3		color;
	void			*spec;
	t_fn_intersect	intersect;
};

typedef struct s_plane
{
	float	a;
}	t_plane;

typedef struct s_sphere
{
	float	radius;
	float	c;
}	t_sphere;

typedef struct s_cylinder
{
	float	r;
	float	h;
	float	y;
}	t_cylinder;

void	prim_init(t_primitive *prim);
void	prim_destroy(void *vprim);

// Intersections
float	i_sphere(void *prim, t_hit *hit);
float	i_plane(void *prim, t_hit *hit);
float	i_cylinder(void *prim, t_hit *hit);

#endif
