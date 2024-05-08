/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:02 by psotto-m          #+#    #+#             */
/*   Updated: 2024/05/08 10:37:04 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vec3.h"

void	tf_from_pos(const t_vec3 *pos, t_transf *t)
{
	tf_look_up(pos, (t_vec3){0, 1.f, 0}, t);
}

bool	is_normal(t_vec3 *v)
{
	return (fabs(v->x) <= 1.f && fabs(v->y) <= 1.f && fabs(v->z) <= 1.f);
}
