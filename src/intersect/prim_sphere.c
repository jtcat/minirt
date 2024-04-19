/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:21:29 by psotto-m          #+#    #+#             */
/*   Updated: 2024/04/19 14:21:30 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

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
