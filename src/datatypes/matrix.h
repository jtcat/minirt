/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:26:43 by jcat              #+#    #+#             */
/*   Updated: 2024/04/07 04:03:35 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <libft.h>
# include "../datatypes/vec3.h"

typedef struct s_mat
{
	float	mat[4][4];
	float	inv[4][4];
}	t_mat;

typedef struct s_transf
{
	t_mat	transl;
	t_mat	rot;
	float	tr_prod[4][4];
	float	rot_inv_prod[4][4];
}	t_transf;

t_vec3	transf_point(float m[4][4], t_vec3 *vec);
t_vec3	transf_vec(float m[4][4], t_vec3 *vec);
void	mat_mult(float m1[4][4], float m2[4][4], float dst[4][4]);
void	rot_from_up(t_vec3 *normal, t_transf *t);
void	transf_from_v3(t_vec3 *v, t_transf *t);
void	mat_zero(t_mat *t);
t_vec3	mat_getpos(t_transf *t);
#endif
