/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:08:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/13 15:05:23 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

typedef bool	(*t_fnIntersect)(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit);

bool	i_plane(void *spec, t_ray *ray, t_vec2 distBound, t_hit *hit)
{
	const t_vec3	up = (t_vec3){0.0, 1.0, 0.0};
	const float		a = v3dot(ray->dir, up);
	const float		d = -v3dot(ray->origin, up) / a;

	(void)spec;
	if (a == 0.f || d < distBound.x || d > distBound.y)
		return (false);
	else
	{
		hit->normal = v3scalef(up, -fsign(a));
		hit->dist = d;
		return (true);
	}
}

// IMPORTANT:	ray dir MUST be normalized!
bool	i_sphere(void *spec, t_ray *ray, t_vec2 bound, t_hit *hit)
{
	const float	r = ((t_sphere *)spec)->radius;
	const float	b = v3dot(ray->origin, v3unit(ray->dir));
	const float	c = v3dot(ray->origin, ray->origin) - r * r;
	float		h;
	float		dist;

	h = b * b - c;
	if (h < 0.f)
		return (false);
	else
	{
		h = sqrt(h);
		dist = -b - h;
		if (dist > bound.x && dist < bound.y)
		{
			hit->normal = v3sum(ray->origin, v3scalef(ray->dir, dist));
			hit->dist = dist;
			return (true);
		}
		dist = -b + h;
		if (dist > bound.x && dist < bound.y)
		{ 
			hit->normal = v3sum(ray->origin, v3scalef(ray->dir, -dist));
			hit->dist = dist;
			return (true);
		}
		return (false);
	}
}

bool	i_cylinder(void *rawspec, t_ray *ray, t_vec2 bound, t_hit *hit)
{
	ray->dir = v3unit(ray->dir);
	t_cylinder const	*spec = (t_cylinder *)rawspec;
	const float			k2 = 1.0 - ray->dir.y * ray->dir.y;
	const float			k1 = v3dot(ray->origin, ray->dir) \
						 - ray->origin.y * ray->dir.y;
	const float			k0 = v3dot(ray->origin, ray->origin) \
						 - ray->origin.y * ray->origin.y - spec->r * spec->r;

	float	h = k1 * k1 - k2 * k0;
	if (h < 0.0)
		return (false);
	h = sqrt(h);
	float	t = (-k1 - h) / k2;

	// body
	float	y = ray->origin.y + t * ray->dir.y;
	if (t > bound.x && t < bound.y && y > -spec->h && y < spec->h )
	{
		hit->dist = t;
		hit->normal = v3scalef(v3sub(v3sum(ray->origin, v3scalef(ray->dir, t)), vec3(0.0,y,0.0)), 1.0f / spec->r);
		return (true);
	}

	// caps
	t = ( ((y < 0.0) ? -spec->h : spec->h) - ray->origin.y) / ray->dir.y;
	if (t > bound.x && t < bound.y && fabs(k1 + k2 * t) < h)
	{
		hit->dist = t;
		hit->normal = vec3(0.0, fsign(y),0.0);
		return (true);
	}
	return (false);
}

void	prim_init(t_primitive *prim)
{
	prim->spec = NULL;
}

void	prim_destroy(void *vprim)
{
	t_primitive	*prim;

	prim = (t_primitive *)vprim;
	if (prim->spec)
		free(prim->spec);
	free(prim);
}
