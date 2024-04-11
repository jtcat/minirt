/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:10:19 by jcat              #+#    #+#             */
/*   Updated: 2024/04/11 14:30:05 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "../utils.h"
#include "vec3.h"

static inline float	tf_inv_trprod(t_transf *t, int i)
{
	return (-t->inv[i][0] * t->mat[0][3] - t->inv[i][1] * t->mat[1][3] - t->inv[i][2] * t->mat[2][3]);
}

static void	tf_update_inv(t_transf	*t)
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

void	tf_look_up(t_vec3 *pos, t_vec3 *up_dir, t_transf *t)
{
	t_vec3	vup = {0.f, 1.f, 0.f};
	t_vec3	xaxis;
	t_vec3	zaxis;

	*up_dir = v3unit(*up_dir);
	xaxis = v3unit(v3cross(vup, *up_dir));
	if (xaxis.x == 0 && xaxis.y == 0 && xaxis.z == 0.f)
	{
		xaxis = (t_vec3){1.f, 0 ,0};
		zaxis = (t_vec3){0.f, 0 , up_dir->y};
	}
	else
		zaxis = v3cross(*up_dir, xaxis);

	t->mat[0][0] = xaxis.x;
	t->mat[0][1] = up_dir->x;
	t->mat[0][2] = zaxis.x;
	t->mat[0][3] = pos->x;
	t->mat[1][0] = xaxis.y;
	t->mat[1][1] = up_dir->y;
	t->mat[1][2] = zaxis.y;
	t->mat[1][3] = pos->y;
	t->mat[2][0] = xaxis.z;
	t->mat[2][1] = up_dir->z;
	t->mat[2][2] = zaxis.z;
	t->mat[2][3] = pos->z;
	t->mat[3][0] = 0.f;
	t->mat[3][1] = 0.f;
	t->mat[3][2] = 0.f;
	t->mat[3][3] = 1.f;

	tf_update_inv(t);
}

void	tf_from_pos(t_vec3 *v, t_transf *t)
{
	t_vec3	vup = {0.f, 1.f, 0.f};

	tf_look_up(v, &vup, t);
}

//static inline float	calc_el(float a[4][4], float b[4][4], int row, int col)
//{
//	return (a[row][0] * b[0][col]
//			+ a[row][1] * b[1][col]
//			+ a[row][2] * b[2][col]
//			+ a[row][3] * b[3][col]);
//}
//
//void	mat_mult(float a[4][4], float b[4][4], float d[4][4])
//{
//	d[0][0] = calc_el(a, b, 0, 0);
//	d[0][1] = calc_el(a, b, 0, 1);
//	d[0][2] = calc_el(a, b, 0, 2);
//	d[0][3] = calc_el(a, b, 0, 3);
//	d[1][0] = calc_el(a, b, 1, 0);
//	d[1][1] = calc_el(a, b, 1, 1);
//	d[1][2] = calc_el(a, b, 1, 2);
//	d[1][3] = calc_el(a, b, 1, 3);
//	d[2][0] = calc_el(a, b, 2, 0);
//	d[2][1] = calc_el(a, b, 2, 1);
//	d[2][2] = calc_el(a, b, 2, 2);
//	d[2][3] = calc_el(a, b, 2, 3);
//	d[3][0] = calc_el(a, b, 3, 0);
//	d[3][1] = calc_el(a, b, 3, 1);
//	d[3][2] = calc_el(a, b, 3, 2);
//	d[3][3] = calc_el(a, b, 3, 3);
//}
//
t_vec3	transf_point(float m[4][4], t_vec3 *v)
{
	return ((t_vec3){
			m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z + m[0][3],
			m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z + m[1][3],
			m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3],
			});
}

t_vec3	transf_vec(float m[4][4], t_vec3 *v)
{
	return ((t_vec3){
			m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z,
			m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z,
			m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z,
			});
}
