/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:28:19 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 12:06:18 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"
#include "../render/rt.h"

static void	n_cyl_body(t_hit *hit)
{
	t_cylinder *const	spec = (t_cylinder *)hit->prim->spec;

	hit->normal = v3unit(v3scalef(v3sub(v3sum(hit->ray.origin,
						v3scalef(hit->ray.dir, hit->bound.y)),
					(t_vec3){0.f, spec->y, 0.f}), 1.f / spec->r));
}

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
