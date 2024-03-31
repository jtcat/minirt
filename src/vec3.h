/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:19:19 by joaoteix          #+#    #+#             */
/*   Updated: 2024/03/31 20:02:51 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include <math.h>

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec3_new(const double x, const double y, const double z);
t_vec3	v3sum(const t_vec3 a, const t_vec3 b);
t_vec3	v3sub(const t_vec3 a, const t_vec3 b);
double	v3dot(const t_vec3 u, const t_vec3 v);
t_vec3	v3cross(const t_vec3 a, const t_vec3 b);
t_vec3	v3unit(const t_vec3 a);
t_vec3	v3scalef(const t_vec3 v, const double f);
t_vec3	v3scalei(const t_vec3 v, const int i);

#endif
