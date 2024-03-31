/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:14 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 21:43:37 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

#include "rt.h"

typedef struct s_plane
{
	t_vec3	normal;
	float	height;	
}	t_plane;

typedef struct s_sphere
{
	t_vec3	pos;
	float	radius;
}	t_sphere;

#endif
