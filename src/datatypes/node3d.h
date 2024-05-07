/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:55:48 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/07 14:53:07 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE3D_H
# define NODE3D_H

# include "matrix.h"

enum e_nodetype
{
	NODE_CAM,
	NODE_LIGHT,
	NODE_PRIM,
};

typedef struct s_node3d
{
	enum e_nodetype	type;
	t_transf		transf;
}	t_node3d;

void	*node3d_subtype_new(size_t type_size, enum e_nodetype node_type);

#endif
