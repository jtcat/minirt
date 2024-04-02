/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:08:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 02:54:02 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

typedef bool	(*t_fnIntersect)(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit);

bool	plane(t_ray *ray, t_vec2 distBound, t_vec3 normal, t_vec3 planeNormal, float planeDist)
{
	float	a;
	float	d;

	a = v3dot(ray->dir, ((t_plane)spec)->normal);
	d = -(v3dot(ray->origin, ((t_plane)spec)->planeNormal) + planeDist) / a;
	if (a > 0. || d < distBound.x || d > distBound.y) {
		return MAX_DIST;
	} else {
		normal = planeNormal;
		return d;
	}
}

bool	iSphere(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit)
{
	const t_sphere	*sphere_spec = (t_sphere *)spec;

	t_vec3	oc;
	float	b;
	float	c;
	float	h;

	oc = v3sub(ray->origin, spec->pos);
	b = v3dot(oc, ray->dir);
	c = v3dot(oc, oc) - spec->radius * spec->radius;
	h = b * b - c;
	if (h < 0.)
		return (false);
	else
	{
		h = sqrt(h);
		c = -b - h;
		b = -b + h;
		if (c >= bound.x && c <= bound.y) {
			hit->normal = v3unit(v3sum(oc, v3scalef(ray->dir, c)));
			bound.y = c;
		} else if (b >= bound.x && b <= bound.y) { 
			hit->normal = v3unit(v3sum(oc, v3scalef(ray->dir, b)));            
			bound.y = b;
		} else 
			return (false);
		return (true);
	}
}

bool	iCylinder(t_ray *ray, float he, float ra )
{
    float k2 = 1.0        - rd.y*rd.y;
    float k1 = dot(ro,rd) - ro.y*rd.y;
    float k0 = dot(ro,ro) - ro.y*ro.y - ra*ra;
    
    float h = k1*k1 - k2*k0;
    if( h<0.0 ) return vec4(-1.0);
    h = sqrt(h);
    float t = (-k1-h)/k2;

    // body
    float y = ro.y + t*rd.y;
    if( y>-he && y<he ) return vec4( t, (ro + t*rd - vec3(0.0,y,0.0))/ra );
    
    // caps
    t = ( ((y<0.0)?-he:he) - ro.y)/rd.y;
    if( abs(k1+k2*t)<h ) return vec4( t, vec3(0.0,sign(y),0.0) );

    return vec4(-1.0);
}

void	prim_init(t_primitive *prim)
{
	prim->spec = NULL;
}

void	prim_destroy(void *vprim)
{
	const t_primitive	*prim = (t_primitive *)vrim;

	if (prim->spec)
		free(prim->spec);
}
