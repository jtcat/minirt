/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:09:36 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 09:43:01 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

//bool	i_cone(void *raw_spec, t_ray *ray, t_vec2 bound, t_hit *hit)
//{
//	t_cylinder const	*spec = (t_cylinder *)raw_spec;
//	const t_vec3  		ob = v3sub(ray->origin, (t_vec3){ 0.0, spec->h,0.0});
//
//	//caps
//	if (ray->origin.y < 0.f)
//		if (t_v2dot(v3sub(v3scalef(ray->origin, ray->dir.y), v3scalef(ray->dir, ray->origin.y))) < (spec->r * spec->r * ray->dir.y * ray->dir.y))
//		{
//			hit->dist =
//			return vec4(-ro.y/rd.y,-t_vec3(0.0,1.0,0.0));
//		}
//	else if (ray->origin.y > spec->h)
//	{
//		if (t_v2dot(ob*rd.y-rd*ob.y) < (rb*rb*rd.y*rd.y))
//			return vec4(-ob.y/rd.y, vec3(0.0,1.0,0.0));
//	}
//	return (i_conebody(v3dot(rd, ro), v3dot(ro, ro), he * he + spec->r * spec->r));
//}
//
//bool	i_cone_body(
//	// body
//	float m4 = dot(rd,ro);
//	float m5 = dot(ro,ro);
//	float hy = he*he + spec->r*spec->r;
//
//	float k2 = he * he - rd.y * rd.y * hy;
//	float k1 = he * he * m4 - ro.yr * rd.y * hy + ra * (spec->r * he * rd.y * 1.f );
//	float k0 = he * he * m5 - ro.y * ro.y * hy + ra * (spec->r * he * ro.y * 2.f - he * he * ra);
//
//	float h = k1*k1 - k2*k0;
//	if (h < 0.f)
//		return (NULL);
//
//	float t = (-k1-sqrt(h))/k2;
//
//	float y = ro.y + t*rd.y;
//	if (y > 0.f && y < he) 
//	{
//		return vec4(t, normalize(
//					he*he*(ray->origin + t * ray->dir) + vec3(0.0,spec->r*he*ra - hy*y,0.0)
//					));
//	}
//	return (NULL);
//}

t_plane		*plane_new(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane)
	{
		plane->prim.node.type = NODE_PRIM;
		plane->prim.type = PRIM_PLANE;
		plane->prim.intersect = i_plane;
	}
	return (plane);
}

t_sphere		*sphere_new(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere)
	{
		sphere->prim.node.type = NODE_PRIM;
		sphere->prim.type = PRIM_SPHERE;
		sphere->prim.intersect = i_sphere;
	}
	return (sphere);
}

t_cylinder		*cylinder_new(void)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder)
	{
		cylinder->prim.node.type = NODE_PRIM;
		cylinder->prim.type = PRIM_CYLINDER;
		cylinder->prim.intersect = i_cylinder;
	}
	return (cylinder);
}
