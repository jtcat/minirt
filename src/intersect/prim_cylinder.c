/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:28:19 by jcat              #+#    #+#             */
/*   Updated: 2024/05/07 19:00:16 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

static void	n_cyl_body(t_hit *hit)
{
	t_cylinder *const	cyl = (t_cylinder *)hit->prim;
	const double		outside = ((v3dot(hit->ray.origin, hit->ray.origin) \
					- hit->ray.origin.y * hit->ray.origin.y)
			> (cyl->r * cyl->r))
		* 2.f - 1.f;

	hit->normal = v3unit(v3scalef(v3sub(v3sum(hit->ray.origin,
						v3scalef(hit->ray.dir, hit->bound.y)),
					(t_vec3){0.f, cyl->y, 0.f}), outside / cyl->r));
}

static void	n_cyl_caps(t_hit *hit)
{
	t_cylinder *const	cyl = (t_cylinder *)hit->prim;
	const double		outside = ((v3dot(hit->ray.origin, hit->ray.origin) \
					- hit->ray.origin.y * hit->ray.origin.y)
			> (cyl->r * cyl->r))
		* 2.f - 1.f;

	hit->normal = (t_vec3){0.f, outside
		* fsign(((t_cylinder *)hit->prim)->y), 0.f};
}

static inline double	i_cyl_body_t(double k1, double k2, double h)
{
	double	t1;
	double	t2;

	t1 = (-k1 - h) / k2;
	t2 = (-k1 + h) / k2;
	if (fmin(t1, t2) < 0)
		return (fmax(t1, t2));
	return (fmin(t1, t2));
}

static inline double	i_cyl_helper(t_cylinder *cyl, t_hit *hit, double k0)
{
	const double	k2 = 1.f - hit->ray.dir.y * hit->ray.dir.y;
	const double	k1 = v3dot(hit->ray.origin, hit->ray.dir) \
					- hit->ray.origin.y * hit->ray.dir.y;
	double			h;
	double			t;

	h = k1 * k1 - k2 * k0;
	if (h < 0.f)
		return (-1.f);
	h = sqrt(h);
	t = i_cyl_body_t(k1, k2, h);
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

double	i_cylinder(t_primitive *cyl, t_hit *hit)
{
	const double			k0 = v3dot(hit->ray.origin, hit->ray.origin)
		- hit->ray.origin.y * hit->ray.origin.y
		- ((t_cylinder *)cyl)->r * ((t_cylinder *)cyl)->r;

	return (i_cyl_helper((t_cylinder *)cyl, hit, k0));
}
