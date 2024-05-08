/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if3_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:12:11 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:06:16 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt_bonus.h"

void	*cycle_sel_attr(const t_node3d *node, void *curr_attr)
{
	if (node->type == NODE_CAM)
		return (&((t_camera *)node)->hfov);
	if (node->type == NODE_PRIM)
	{
		if (((t_primitive *)node)->type == PRIM_SPHERE)
			return (&((t_sphere *)node)->r);
		if (((t_primitive *)node)->type == PRIM_CYLINDER)
		{
			if (curr_attr == &((t_cylinder *)node)->h)
				return (&((t_cylinder *)node)->r);
			return (&((t_cylinder *)node)->h);
		}
	}
	return (NULL);
}

t_node3d	*if_get_sel_node(const t_ifctx *ifctx)
{
	return (ifctx->rtctx->node_ref_list[ifctx->node_index]);
}

void	poll_obj_sel(const int key, t_ifctx *ifctx)
{
	t_node3d *const	node = if_get_sel_node(ifctx);

	ifctx->node_attr_ref = NULL;
	if (key == XK_q)
		--ifctx->node_index;
	else if (key == XK_e)
		++ifctx->node_index;
	ifctx->node_index = clamp(ifctx->node_index, 0, ifctx->rtctx->node_n - 1);
	ifctx->node_attr_ref = cycle_sel_attr(node, ifctx->node_attr_ref);
}
