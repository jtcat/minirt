/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:06:32 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/07 20:14:40 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec3	transf_point(const double m[4][4], const t_vec3 *v)
{
	return ((t_vec3){
		m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z + m[0][3],
		m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z + m[1][3],
		m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3],
		});
}

t_vec3	transf_vec(const double m[4][4], const t_vec3 *v)
{
	return ((t_vec3){
		m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z,
		m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z,
		m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z,
			});
}

// Left transforms right
// mat mult, store in r;
void	tf_transform(t_transf *l, t_transf *r, t_transf *dst)
{
	double	res[4][4];
	int		i;
	int		j;

	mat_mult(l->mat, r->mat, res);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst->mat[i][j] = res[i][j];
			j++;
		}
		i++;
	}
	tf_update_inv(dst);
}

void	tf_translate(t_transf *l, const t_vec3 *transl)
{
	l->mat[0][3] += transl->x;
	l->mat[1][3] += transl->y;
	l->mat[2][3] += transl->z;
	tf_update_inv(l);
}

t_vec3	tf_get_vec(const t_transf *t, int index)
{
	return ((t_vec3){t->mat[0][index], t->mat[1][index], t->mat[2][index]});
}
