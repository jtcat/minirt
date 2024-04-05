/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:10:19 by jcat              #+#    #+#             */
/*   Updated: 2024/04/05 20:47:29 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mat_zero(t_transf *t)
{
	ft_bzero(t->mat, sizeof(t->mat));
	ft_bzero(t->mat, sizeof(t->inv));
}

static inline void	mat_4x4_transpose(float m[4][4], float dst[4][4])
{
    dst[0][0] = m[0][0];
    dst[1][0] = m[0][1];
    dst[2][0] = m[0][2];
    dst[3][0] = m[0][3];
    dst[0][1] = m[1][0];
    dst[1][1] = m[1][1];
    dst[2][1] = m[1][2];
    dst[3][1] = m[1][3];
    dst[0][2] = m[2][0];
    dst[1][2] = m[2][1];
    dst[2][2] = m[2][2];
    dst[3][2] = m[2][3];
    dst[0][3] = m[3][0];
    dst[1][3] = m[3][1];
    dst[2][3] = m[3][2];
    dst[3][3] = m[3][3];
}

static inline void	calc_transl_inv(t_transf *t)
{
	t->inv[0][3] = -t->mat[0][3];
	t->inv[1][3] = -t->mat[1][3];
	t->inv[2][3] = -t->mat[2][3];
}

void	transform_transl(t_transf *t, t_vec3 *v)
{
	t->mat[0][3] += v->x;
	t->mat[1][3] += v->y;
	t->mat[2][3] += v->z;
	calc_transl_inv(t);
}

//void	transform_rot(t_transf *t, t_vec3 *v)
//{
//}

void	transf_from_v3(t_vec3 *v, t_transf *t)
{
	mat_zero(t);
	t->mat[0][3] = v->x;
	t->mat[1][3] = v->y;
	t->mat[2][3] = v->z;
	t->mat[0][0] = 1;
	t->mat[1][1] = 1;
	t->mat[2][2] = 1;
	t->mat[3][3] = 1;
	calc_transl_inv(t);
	t->inv[0][0] = 1;
	t->inv[1][1] = 1;
	t->inv[2][2] = 1;
	t->inv[3][3] = 1;
}

static inline float	calc_el(float a[4][4], float b[4][4], int row, int col) {
	return (a[row][0] * b[0][col]
		+ a[row][1] * b[1][col]
		+ a[row][2] * b[2][col]
		+ a[row][3] * b[3][col]);
}

void	mat_mult(float a[4][4], float b[4][4], float d[4][4])
{
	d[0][0] = calc_el(a, b, 0, 0);
    d[0][1] = calc_el(a, b, 0, 1);
    d[0][2] = calc_el(a, b, 0, 2);
    d[0][3] = calc_el(a, b, 0, 3);
    d[1][0] = calc_el(a, b, 1, 0);
    d[1][1] = calc_el(a, b, 1, 1);
    d[1][2] = calc_el(a, b, 1, 2);
    d[1][3] = calc_el(a, b, 1, 3);
    d[2][0] = calc_el(a, b, 2, 0);
    d[2][1] = calc_el(a, b, 2, 1);
    d[2][2] = calc_el(a, b, 2, 2);
    d[2][3] = calc_el(a, b, 2, 3);
    d[3][0] = calc_el(a, b, 3, 0);
    d[3][1] = calc_el(a, b, 3, 1);
    d[3][2] = calc_el(a, b, 3, 2);
    d[3][3] = calc_el(a, b, 3, 3);
}

t_vec3	mat_vec3_mult(float m[4][4], t_vec3 *vec)
{
	t_transf	pos;
	t_transf	prod;

	transf_from_v3(vec, &pos);
	mat_mult(m, pos.mat, prod.mat);
	return ((t_vec3){prod.mat[0][3], prod.mat[1][3], prod.mat[2][3]});
}

void	rot_from_up(t_vec3 *up, t_transf *t)
{
	const t_vec3 ff = {0.f, 0.f, -1.f};
	const t_vec3 xaxis = v3unit(v3cross(*up, ff));
	const t_vec3 zaxis = v3unit(v3cross(*up, xaxis));

	t->mat[0][0] = xaxis.x;
	t->mat[1][0] = up->x;
	t->mat[2][0] = zaxis.x;

	t->mat[0][1] = xaxis.y;
	t->mat[1][1] = up->y;
	t->mat[2][1] = zaxis.y;

	t->mat[0][2] = xaxis.z;
	t->mat[1][2] = up->z;
	t->mat[2][2] = zaxis.z;

	t->mat[0][3] = 0.f;
	t->mat[1][3] = 0.f;
	t->mat[2][3] = 0.f;
	t->mat[3][0] = 0.f;
	t->mat[3][1] = 0.f;
	t->mat[3][2] = 0.f;
	t->mat[3][3] = 1.f;
	mat_4x4_transpose(t->mat, t->inv);
}

t_vec3	mat_getpos(t_transf *t)
{
	return ((t_vec3){t->mat[0][3], t->mat[1][3], t->mat[2][3]});
}
