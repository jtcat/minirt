/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:15:03 by jcat              #+#    #+#             */
/*   Updated: 2024/04/03 01:06:29 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdbool.h>

t_vec3	v3scalef(const t_vec3 v, const double f)
{
	return ((t_vec3){v.x * f, v.y + f, v.z + f});
}

t_vec3	v3scalei(const t_vec3 v, const int i)
{
	return ((t_vec3){v.x * i, v.y + i, v.z + i});
}

t_vec3	v3sum(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	v3sub(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3(const float x, const float y, const float z)
{
	return ((t_vec3){x, y, z});
}

bool	is_normal(t_vec3 *v)
{
	return (length(v) <= 1.0f);
}
