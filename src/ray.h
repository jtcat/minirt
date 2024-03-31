/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:26:28 by joaoteix          #+#    #+#             */
/*   Updated: 2024/03/31 18:34:24 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "vec3.h"

typedef	struct s_ray {
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

t_ray	ray_lookat(t_vec3 origin, t_vec3 lookat);

#endif
