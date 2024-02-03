/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:19:19 by joaoteix          #+#    #+#             */
/*   Updated: 2024/02/03 16:47:24 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include <math.h>

typedef s_vec3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec3_new(void);
t_vec3	sum(t_vec3 *a, t_vec3 *b);
t_vec3	subtract(t_vec3 *a, t_vec3 *b);
t_vec3	cross(t_vec3 *a, t_vec3 *b);
t_vec3	unit(t_vec3 *a);
t_vec3	v3scalef(double f, t_vec3 *v);

#endif
