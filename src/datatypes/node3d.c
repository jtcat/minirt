/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 01:56:55 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/24 01:57:39 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node3d.h"

void	*node3d_subtype_new(size_t type_size, enum e_nodetype node_type)
{
	t_node3d	*new_node;

	new_node = malloc(type_size);
	if (new_node)
		new_node->type = node_type;
	return (new_node);
}
