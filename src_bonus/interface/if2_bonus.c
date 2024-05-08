/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if2_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:13:08 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:06:07 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt_bonus.h"
#include "if_bonus.h"

static char	*get_prim_attr_name(const t_node3d *node, void *attrib_ptr)
{
	if (node->type == NODE_CAM)
		return ("FOV");
	if (node->type == NODE_PRIM)
	{
		if (((t_primitive *)node)->type == PRIM_SPHERE)
			return ("Radius");
		if (((t_primitive *)node)->type == PRIM_CYLINDER)
		{
			if (attrib_ptr == &((t_cylinder *)node)->h)
				return ("Height");
			if (attrib_ptr == &((t_cylinder *)node)->r)
				return ("Radius");
		}
	}
	return ("None");
}

static void	cycle_if_mode(t_ifctx *const ifctx)
{
	if (++ifctx->mode > IF_MODE_LAST)
		ifctx->mode = IF_MODE_FIRST;
}

void	poll_interface(const int key, t_rtctx *rtctx)
{
	if (key == XK_f)
		cycle_if_mode(&rtctx->ifctx);
	if (rtctx->ifctx.mode == IF_MODE_TRANSLATE)
		poll_translate(key, &rtctx->ifctx);
	if (rtctx->ifctx.mode == IF_MODE_ROTATE)
		poll_rotate(key, &rtctx->ifctx);
	if (rtctx->ifctx.mode == IF_MODE_MORPH)
		poll_node_morph(key, &rtctx->ifctx);
	poll_obj_sel(key, &rtctx->ifctx);
}

void	ifctx_init(t_ifctx *ifctx, t_rtctx *rtctx)
{
	ifctx->visible = true;
	ifctx->rtctx = rtctx;
	ifctx->mode = IF_MODE_TRANSLATE;
	ifctx->node_index = 0;
	ifctx->node_attr_ref = NULL;
}

void	display_interface(const t_ifctx *ifctx)
{
	char *const	mode_names[] = {"Translate", "Rotate", "Morph"};
	char *const	obj_types[] = {"Camera", "Light", "Primitive"};
	char *const	prim_names[] = {"Plane", "Sphere", "Cylinder"};
	char		*status_str;

	if (!ifctx->visible)
		return ;
	status_str = ft_strjoin("MODE: ", mode_names[ifctx->mode]);
	ft_strjoin_morph(&status_str, " | OBJECT TYPE: ");
	ft_strjoin_morph(&status_str, obj_types[if_get_sel_node(ifctx)->type]);
	if (if_get_sel_node(ifctx)->type == NODE_PRIM)
	{
		ft_strjoin_morph(&status_str, " | PRIMITIVE TYPE: ");
		ft_strjoin_morph(&status_str,
			prim_names[((t_primitive *)if_get_sel_node(ifctx))->type]);
	}
	if (ifctx->node_attr_ref)
	{
		ft_strjoin_morph(&status_str, " | ATTRIBUTE: ");
		ft_strjoin_morph(&status_str,
			get_prim_attr_name(if_get_sel_node(ifctx), ifctx->node_attr_ref));
	}
	mlx_string_put(ifctx->rtctx->mlx_ptr,
		ifctx->rtctx->window_ptr, 20, 20, (1 << 24) - 1, status_str);
	free(status_str);
}
