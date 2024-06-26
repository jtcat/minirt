/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:26:43 by jcat              #+#    #+#             */
/*   Updated: 2024/05/07 20:13:01 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <libft.h>
# include "../datatypes/vec3.h"

typedef struct s_transf
{
	double	mat[4][4];
	double	inv[4][4];
}	t_transf;

void	mat_mult(double a[4][4], double b[4][4], double d[4][4]);

void	tf_translate(t_transf *l, const t_vec3 *transl);
void	tf_transform(t_transf *l, t_transf *r, t_transf *dst);

t_vec3	transf_point(const double m[4][4], const t_vec3 *v);
t_vec3	transf_vec(const double m[4][4], const t_vec3 *v);

t_vec3	tf_get_vec(const t_transf *t, int index);

void	tf_from_pos(const t_vec3 *pos, t_transf *t);
void	tf_look_up(const t_vec3 *pos, t_vec3 up_dir, t_transf *t);
void	tf_look_along(const t_vec3 *pos, t_vec3 lookdir, t_transf *t);
void	tf_update_inv(t_transf *t);
#endif
