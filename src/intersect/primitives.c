/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:28:19 by jcat              #+#    #+#             */
/*   Updated: 2024/04/15 17:25:47 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

static void	n_plane(t_hit *hit)
{
	hit->normal = (t_vec3){0.f,
		-fsign(((t_plane *)hit->prim->spec)->a), 0.f};
}

float	i_plane(void *spec, t_hit *hit)
{
	const t_vec3	up = (t_vec3){0.0, 1.0, 0.0};
	const float		a = v3dot(hit->ray.dir, up);
	const float		d = -v3dot(hit->ray.origin, up) / a;

	if (a == 0.f || d < hit->bound.x || d > hit->bound.y)
		return (-1.f);
	else
	{
		((t_plane *)spec)->a = a;
		hit->norm_fn = n_plane;
		return (d);
	}
}

static void	n_sphere(t_hit *hit)
{
	hit->normal = v3unit(v3sum(hit->ray.origin,
				v3scalef(hit->ray.dir,
					fsign(((t_sphere *)hit->prim->spec)->c) *hit->bound.y)));
}

// IMPORTANT:	ray dir MUST be normalized!
float	i_sphere(void *spec, t_hit *hit)
{
	const float	r = ((t_sphere *)spec)->radius;
	const float	b = v3dot(hit->ray.origin, hit->ray.dir);
	const float	c = v3dot(hit->ray.origin, hit->ray.origin) - r * r;
	float		h;
	float		t;

	h = b * b - c;
	if (h < 0.f)
		return (-1.f);
	else
	{
		h = sqrt(h);
		t = -b - fsign(c) * h;
		if (t > hit->bound.x && t < hit->bound.y)
		{
			((t_sphere *)spec)->c = c;
			hit->norm_fn = n_sphere;
			return (t);
		}
		return (-1.f);
	}
}

static void	n_cyl_body(t_hit *hit)
{		
	t_cylinder *const	spec = (t_cylinder *)hit->prim->spec;

	hit->normal = v3unit(v3scalef(v3sub(v3sum(hit->ray.origin,
						v3scalef(hit->ray.dir, hit->bound.y)),
					(t_vec3){0.f, spec->y, 0.f}), 1.f / spec->r));
}

// h = y
static void	n_cyl_caps(t_hit *hit)
{
	hit->normal = (t_vec3){0.f, fsign(((t_cylinder *)hit->prim->spec)->y), 0.f};
}

static inline float	i_cyl_helper(t_cylinder *spec, t_hit *hit, float k0)
{
	const float	k2 = 1.f - hit->ray.dir.y * hit->ray.dir.y;
	const float	k1 = v3dot(hit->ray.origin, hit->ray.dir) \
					- hit->ray.origin.y * hit->ray.dir.y;
	float		h;
	float		t;

	h = k1 * k1 - k2 * k0;
	if (h < 0.f)
		return (-1.f);
	h = sqrt(h);
	t = (-k1 - h) / k2;
	spec->y = hit->ray.origin.y + t * hit->ray.dir.y;
	if (t > hit->bound.x && t < hit->bound.y
		&& spec->y > -spec->h && spec->y < spec->h)
	{
		hit->norm_fn = n_cyl_body;
		return (t);
	}
	t = (ftern(spec->y < 0.f, -spec->h, spec->h)
			- hit->ray.origin.y) / hit->ray.dir.y;
	if (!(t > hit->bound.x && t < hit->bound.y && fabs(k1 + k2 * t) < h))
		return (-1.f);
	hit->norm_fn = n_cyl_caps;
	return (t);
}

float	i_cylinder(void *rawspec, t_hit *hit)
{
	t_cylinder *const	spec = (t_cylinder *)rawspec;
	const float			k0 = v3dot(hit->ray.origin, hit->ray.origin)
		- hit->ray.origin.y * hit->ray.origin.y
		- spec->r * spec->r;

	return (i_cyl_helper(spec, hit, k0));
}

void	prim_destroy(void *vprim)
{
	t_primitive	*prim;

	prim = (t_primitive *)vprim;
	if (prim->spec)
		free(prim->spec);
	free(prim);
}
