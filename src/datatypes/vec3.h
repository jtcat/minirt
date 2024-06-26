/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:19:19 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/05 16:42:11 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

double	v3length(t_vec3 *v);
bool	is_normal(t_vec3 *v);

t_vec3	vec3(const double x, const double y, const double z);
t_vec3	v3sum(const t_vec3 a, const t_vec3 b);
t_vec3	v3sub(const t_vec3 a, const t_vec3 b);
double	v3dot(const t_vec3 u, const t_vec3 v);
t_vec3	v3cross(const t_vec3 a, const t_vec3 b);
t_vec3	v3unit(const t_vec3 a);
t_vec3	v3scalef(const t_vec3 v, const double f);
t_vec3	v3scalei(const t_vec3 v, const int i);

#endif
