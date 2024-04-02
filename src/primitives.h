/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:14 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 00:58:36 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

#include "vec3.h"
#include "vec2.h"
#include "ray.h"
#include "argb.h"
#include <stdbool.h>

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


typedef struct s_plane
{
	t_vec3	normal;
	float	height;	
}	t_plane;

typedef struct s_sphere
{
	t_vec3	pos;
	float	radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3	pos;
	float	radius;
	float	height;
}	t_cylinder;

void	prim_init(t_primitive *prim);
void	prim_destroy(void *vprim);

// Intersections
bool	iSphere(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit);
#endif
