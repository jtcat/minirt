/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:28:19 by jcat              #+#    #+#             */
/*   Updated: 2024/04/24 12:22:17 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

static void	n_cyl_body(t_hit *hit)
{		
	t_cylinder *const	cyl = (t_cylinder *)hit->prim;

	hit->normal = v3unit(v3scalef(v3sub(v3sum(hit->ray.origin,
						v3scalef(hit->ray.dir, hit->bound.y)),
					(t_vec3){0.f, cyl->y, 0.f}), 1.f / cyl->r));
}

static void	n_cyl_caps(t_hit *hit)
{
	hit->normal = (t_vec3){0.f, fsign(((t_cylinder *)hit->prim)->y), 0.f};
}

static inline float	i_cyl_helper(t_cylinder *cyl, t_hit *hit, float k0)
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
	cyl->y = hit->ray.origin.y + t * hit->ray.dir.y;
	if (t > hit->bound.x && t < hit->bound.y
		&& cyl->y > -cyl->h && cyl->y < cyl->h)
	{
		hit->norm_fn = n_cyl_body;
		return (t);
	}
	t = (ftern(cyl->y < 0.f, -cyl->h, cyl->h)
			- hit->ray.origin.y) / hit->ray.dir.y;
	if (!(t > hit->bound.x && t < hit->bound.y && fabs(k1 + k2 * t) < h))
		return (-1.f);
	hit->norm_fn = n_cyl_caps;
	return (t);
}

float	i_cylinder(t_primitive *cyl, t_hit *hit)
{
	const float			k0 = v3dot(hit->ray.origin, hit->ray.origin)
		- hit->ray.origin.y * hit->ray.origin.y
		- ((t_cylinder *)cyl)->r * ((t_cylinder *)cyl)->r;

	return (i_cyl_helper((t_cylinder *)cyl, hit, k0));
}
