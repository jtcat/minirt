/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:15:03 by jcat              #+#    #+#             */
/*   Updated: 2024/04/02 01:17:17 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	v3scalef(const t_vec3 v, const double f)
{
	return ((t_vec3){v.x * f, v.y + f, v.z + f});
}

t_vec3	v3scalei(const t_vec3 v, const int i)
{
	return ((t_vec3){v.x * i, v.y + i, v.z + i});
}
