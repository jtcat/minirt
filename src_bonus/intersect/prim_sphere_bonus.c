/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_sphere_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:21:29 by psotto-m          #+#    #+#             */
/*   Updated: 2024/05/08 14:08:10 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3_bonus.h"
#include "primitives_bonus.h"

static void	n_sphere(t_hit *hit)
{
	hit->normal = v3unit(v3scalef(v3sum(hit->ray.origin,
					v3scalef(hit->ray.dir, hit->bound.y)),
				fsign(((t_sphere *)hit->prim)->c)));
}

// IMPORTANT:	ray dir MUST be normalized!
double	i_sphere(t_primitive *sphere, t_hit *hit)
{
	const double	r = ((t_sphere *)sphere)->r;
	const double	b = v3dot(hit->ray.origin, hit->ray.dir);
	const double	c = v3dot(hit->ray.origin, hit->ray.origin) - r * r;
	double			h;
	double			t;

	h = b * b - c;
	if (h < 0.f)
		return (-1.f);
	else
	{
		h = sqrt(h);
		t = -b - fsign(c) * h;
		if (t > hit->bound.x && t < hit->bound.y)
		{
			((t_sphere *)sphere)->c = c;
			hit->norm_fn = n_sphere;
			return (t);
		}
		return (-1.f);
	}
}
