/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:08:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 02:37:52 by jcat             ###   ########.fr       */
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

float cylinder( in vec3 ro, in vec3 rd, in vec2 distBound, inout vec3 normal,
		in vec3 pa, in vec3 pb, float ra ) {
	vec3 ca = pb-pa;
	vec3 oc = ro-pa;

	float caca = dot(ca,ca);
	float card = dot(ca,rd);
	float caoc = dot(ca,oc);

	float a = caca - card*card;
	float b = caca*dot( oc, rd) - caoc*card;
	float c = caca*dot( oc, oc) - caoc*caoc - ra*ra*caca;
	float h = b*b - a*c;

	if (h < 0.) return MAX_DIST;

	h = sqrt(h);
	float d = (-b-h)/a;

	float y = caoc + d*card;
	if (y > 0. && y < caca && d >= distBound.x && d <= distBound.y) {
		normal = (oc+d*rd-ca*y/caca)/ra;
		return d;
	}

	d = ((y < 0. ? 0. : caca) - caoc)/card;

	if( abs(b+a*d) < h && d >= distBound.x && d <= distBound.y) {
		normal = normalize(ca*sign(y)/caca);
		return d;
	} else {
		return MAX_DIST;
	}
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
