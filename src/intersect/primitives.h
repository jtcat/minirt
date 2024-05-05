/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:14 by jcat              #+#    #+#             */
/*   Updated: 2024/05/05 16:34:46 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "../datatypes/node3d.h"
# include "../datatypes/matrix.h"
# include "../datatypes/vec3.h"
# include "../datatypes/vec2.h"
# include "../datatypes/argb.h"
# include "../utils.h"
# include <stdlib.h>
# include <stdbool.h>
# include "../datatypes/ray.h"

enum e_primtype
{
	PRIM_PLANE,
	PRIM_SPHERE,
	PRIM_CYLINDER
};

typedef struct s_primitive	t_primitive;
typedef struct s_hit	t_hit;

typedef void(*t_fn_norm)(t_hit *hit);
typedef double(*t_fn_intersect)(t_primitive *prim, t_hit *hit);

struct s_hit
{
	t_primitive	*prim;
	t_ray		ray;
	t_vec3		normal;
	t_vec2		bound;
	t_fn_norm	norm_fn;
};

// Inherits node3d
// Virtual
struct s_primitive
{
	t_node3d		node;
	enum e_primtype	type;
	t_color3		color;
	t_fn_intersect	intersect;
};

// Inherits primitive
typedef struct s_plane
{
	t_primitive	prim;
	double		a;
}	t_plane;

// Inherits primitive
typedef struct s_sphere
{
	t_primitive	prim;
	double		r;
	double		c;
}	t_sphere;

// Inherits primitive
typedef struct s_cylinder
{
	t_primitive	prim;
	double		r;
	double		h;
	double		y;
}	t_cylinder;

// Contructors
t_plane		*plane_new(void);
t_sphere	*sphere_new(void);
t_cylinder	*cylinder_new(void);

// Intersections
double	i_sphere(t_primitive *sphere, t_hit *hit);
double	i_plane(t_primitive *plane, t_hit *hit);
double	i_cylinder(t_primitive *cyl, t_hit *hit);

#endif
