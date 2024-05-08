/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node3d_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 01:56:55 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:02:52 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node3d_bonus.h"

void	*node3d_subtype_new(size_t type_size, enum e_nodetype node_type)
{
	t_node3d	*new_node;

	new_node = malloc(type_size);
	if (new_node)
		new_node->type = node_type;
	return (new_node);
}
