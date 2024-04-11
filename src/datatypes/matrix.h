/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:26:43 by jcat              #+#    #+#             */
/*   Updated: 2024/04/10 23:17:16 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <libft.h>
# include "../datatypes/vec3.h"

typedef struct s_transf
{
	float	mat[4][4];
	float	inv[4][4];
}	t_transf;

t_vec3	transf_point(float m[4][4], t_vec3 *vec);
t_vec3	transf_vec(float m[4][4], t_vec3 *vec);
void	tf_from_pos(t_vec3 *pos, t_transf *t);
void	tf_look_up(t_vec3 *pos, t_vec3 *up_dir, t_transf *t);
void	mat_mult(float m1[4][4], float m2[4][4], float dst[4][4]);
void	mat_zero(float m[4][4]);
t_vec3	mat_getpos(t_transf *t);
#endif
