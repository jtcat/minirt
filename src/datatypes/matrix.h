/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:26:43 by jcat              #+#    #+#             */
/*   Updated: 2024/04/26 18:53:24 by joaoteix         ###   ########.fr       */
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

void	mat_mult(float a[4][4], float b[4][4], float d[4][4]);

void	tf_translate(t_transf *l, const t_vec3 *transl);
void	tf_transform(t_transf *a, t_transf *b);

t_vec3	transf_point(const float m[4][4], const t_vec3 *v);
t_vec3	transf_vec(const float m[4][4], const t_vec3 *v);

t_vec3	tf_get_pos(const t_transf *t);
t_vec3	tf_get_vec(const t_transf *t, int index);

void	tf_from_pos(const t_vec3 *pos, t_transf *t);
void	tf_look_up(const t_vec3 *pos, t_vec3 up_dir, t_transf *t);
void	tf_look_along(const t_vec3 *pos, t_vec3 lookdir, t_transf *t);
#endif
