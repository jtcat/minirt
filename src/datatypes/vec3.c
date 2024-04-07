/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:44:26 by jcat              #+#    #+#             */
/*   Updated: 2024/04/06 23:46:48 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float	length_squared(t_vec3 *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
} 

float	v3length(t_vec3 *v)
{
	return (sqrt(length_squared(v)));
}

float	v3dot(const t_vec3 u, const t_vec3 v) {
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
	const float	len = v3length(&v);

	return (v3scalef(v, 1.0f / (len + (len == 0.f))));
}
