/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:55:48 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/24 01:57:37 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE3D_H
# define NODE3D_H

#include "matrix.h"

enum e_nodetype {NODE_CAM, NODE_PRIM, NODE_LIGHT};

typedef struct s_node3d
{
	enum e_nodetype	type;
	t_transf		transf;
}	t_node3d;

void	*node3d_subtype_new(size_t type_size, enum e_nodetype node_type);

#endif
