/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:10:19 by jcat              #+#    #+#             */
/*   Updated: 2024/05/02 17:07:49 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vec3.h"

static inline float	tf_inv_trprod(t_transf *t, const int i)
{
	return (-t->inv[i][0] * t->mat[0][3]
			- t->inv[i][1] * t->mat[1][3]
			- t->inv[i][2] * t->mat[2][3]);
}

static void	tf_update_inv(t_transf *t)
{
	t->inv[0][0] = t->mat[0][0];
	t->inv[0][1] = t->mat[1][0];
	t->inv[0][2] = t->mat[2][0];
	t->inv[0][3] = tf_inv_trprod(t, 0);
	t->inv[1][0] = t->mat[0][1];
	t->inv[1][1] = t->mat[1][1];
	t->inv[1][2] = t->mat[2][1];
	t->inv[1][3] = tf_inv_trprod(t, 1);
	t->inv[2][0] = t->mat[0][2];
	t->inv[2][1] = t->mat[1][2];
	t->inv[2][2] = t->mat[2][2];
	t->inv[2][3] = tf_inv_trprod(t, 2);
	t->inv[3][0] = 0.f;
	t->inv[3][1] = 0.f;
	t->inv[3][2] = 0.f;
	t->inv[3][3] = 1;
}

t_vec3	tf_get_vec(const t_transf *t, int index)
{
	return ((t_vec3){t->mat[0][index], t->mat[1][index], t->mat[2][index]});
}

t_vec3	tf_get_pos(const t_transf *t)
{
	return (tf_get_vec(t, 3));
}

static inline void	set_mat_vec(t_transf *t, t_vec3 vec, int vindex)
{
	t->mat[0][vindex] = vec.x;
	t->mat[1][vindex] = vec.y;
	t->mat[2][vindex] = vec.z;
}

void	tf_look_along(const t_vec3 *pos, t_vec3 lookdir, t_transf *t)
{
	const t_vec3	vup = {0.f, 1.f, 0.f};
	t_vec3			xaxis;
	t_vec3			yaxis;

	lookdir = v3unit(lookdir);
	xaxis = v3unit(v3cross(vup, lookdir));
	if (xaxis.x == 0 && xaxis.y == 0 && xaxis.z == 0.f)
		xaxis = (t_vec3){1.f, 0, 0};
	yaxis = v3cross(lookdir, xaxis);
	set_mat_vec(t, xaxis, 0);
	set_mat_vec(t, yaxis, 1);
	set_mat_vec(t, lookdir, 2);
	set_mat_vec(t, *pos, 3);
	t->mat[3][0] = 0;
	t->mat[3][1] = 0;
	t->mat[3][2] = 0;
	t->mat[3][3] = 1;
	tf_update_inv(t);
}

void	tf_look_up(const t_vec3 *pos, t_vec3 up_dir, t_transf *t)
{
	const t_vec3	vup = {0.f, 1.f, 0.f};
	t_vec3			xaxis;
	t_vec3			zaxis;

	up_dir = v3unit(up_dir);
	xaxis = v3unit(v3cross(up_dir, vup));
	if (xaxis.x == 0 && xaxis.y == 0 && xaxis.z == 0.f)
		xaxis = (t_vec3){1.f, 0, 0};
	zaxis = v3cross(xaxis, up_dir);
	set_mat_vec(t, xaxis, 0);
	set_mat_vec(t, up_dir, 1);
	set_mat_vec(t, zaxis, 2);
	set_mat_vec(t, *pos, 3);
	t->mat[3][0] = 0;
	t->mat[3][1] = 0;
	t->mat[3][2] = 0;
	t->mat[3][3] = 1;
	tf_update_inv(t);
}

t_vec3	transf_point(const float m[4][4], const t_vec3 *v)
{
	return ((t_vec3){
		m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z + m[0][3],
		m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z + m[1][3],
		m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3],
		});
}

t_vec3	transf_vec(const float m[4][4], const t_vec3 *v)
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
	float	res[4][4];
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
