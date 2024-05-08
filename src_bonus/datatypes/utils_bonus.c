/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:02 by psotto-m          #+#    #+#             */
/*   Updated: 2024/05/08 14:03:24 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"
#include "vec3_bonus.h"

void	tf_from_pos(const t_vec3 *pos, t_transf *t)
{
	tf_look_up(pos, (t_vec3){0, 1.f, 0}, t);
}

bool	is_normal(t_vec3 *v)
{
	return (fabs(v->x) <= 1.f && fabs(v->y) <= 1.f && fabs(v->z) <= 1.f);
}
