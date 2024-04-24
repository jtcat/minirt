/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:22:57 by psotto-m          #+#    #+#             */
/*   Updated: 2024/04/24 12:22:05 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

static void	n_plane(t_hit *hit)
{
	hit->normal = (t_vec3){0.f, -fsign(((t_plane *)hit->prim)->a), 0.f};
}

float	i_plane(t_primitive *plane, t_hit *hit)
{
	const t_vec3	up = (t_vec3){0.0, 1.0, 0.0};
	const float		a = v3dot(hit->ray.dir, up);
	const float		d = -v3dot(hit->ray.origin, up) / a;

	if (a == 0.f || d < hit->bound.x || d > hit->bound.y)
		return (-1.f);
	else
	{
		((t_plane *)plane)->a = a;
		hit->norm_fn = n_plane;
		return (d);
	}
}
