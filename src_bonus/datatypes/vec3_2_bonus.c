/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:15:03 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 14:03:43 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "vec3_bonus.h"

t_vec3	v3scalef(const t_vec3 v, const double f)
{
	return ((t_vec3){v.x * f, v.y * f, v.z * f});
}

t_vec3	v3scalei(const t_vec3 v, const int i)
{
	return ((t_vec3){v.x * i, v.y * i, v.z * i});
}

t_vec3	v3sum(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	v3sub(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3(const double x, const double y, const double z)
{
	return ((t_vec3){x, y, z});
}
