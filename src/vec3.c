/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:44:26 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 01:12:33 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

double length_squared(t_vec3 *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
} 

double length(t_vec3 *v)
{
	return (sqrt(length_squared(v)));
}

double	v3dot(const t_vec3 u, const t_vec3 v) {
	return (u.x * v.x
		+ u.y * v.y
		+ u.z * v.z);
}

t_vec3 v3cross(const t_vec3 u, const t_vec3 v) {
	return ((t_vec3){u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x});
}

t_vec3 v3unit(t_vec3 v) {
	return (v3scalef(v, 1 / length(&v)));
}

t_vec3	v3sum(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	v3sub(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
