/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:59:30 by jcat              #+#    #+#             */
/*   Updated: 2024/04/25 00:14:41 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt.h"
#include "if_utils.h"
#include <stdio.h>

static char	*get_prim_attr_name(const t_node3d *node, void *attrib_ptr)
{
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

static void	*cycle_sel_attr(const t_primitive *obj, void *curr_attr)
{
	if (obj->type == PRIM_SPHERE)
		return (&((t_sphere *)obj)->r);
	if (obj->type == PRIM_CYLINDER)
	{
		if (curr_attr == &((t_cylinder *)obj)->h)
			return (&((t_cylinder *)obj)->r);
		return (&((t_cylinder *)obj)->h);
	}
	return (NULL);
}

t_node3d	*if_get_sel_node(const t_ifctx *ifctx)
{
	return (ifctx->rtctx->node_ref_list[ifctx->node_index]);
}

//static void	poll_rotate(const int key, t_ifctx *ifctx)
//{
//	t_transf	rot_mat;
//
//	// W and S rotate around object X-Axis
//	// A and D rotate around object Z-Axis
//	transform_apply(&if_get_sel_node(ifctx)->transf, &rot_mat);
//}

static void	poll_translate(const int key, t_ifctx * const ifctx)
{
	t_node3d *const	node = if_get_sel_node(ifctx);
	const t_vec3	transl = {(key == XK_d) - (key == XK_a),
					(key == XK_space) - (key == XK_Control_L),
					(key == XK_w) - (key == XK_s)};
	t_transf		transf;

	if (node->type == NODE_CAM)
	{
		tf_from_pos(&transl, &transf);
		tf_transform(&node->transf, &transf);
	}
	else
		tf_translate(&node->transf, &transl);
}

static void	poll_prim_morph(const int key, t_ifctx *ifctx)
{
	t_node3d *const		sel_node = if_get_sel_node(ifctx);
	t_primitive *const	sel_prim = (t_primitive *)sel_node;

	if (sel_node->type != NODE_PRIM)
		return ;
	if (key == XK_d)
		ifctx->node_attr_ref = cycle_sel_attr(sel_prim, ifctx->node_attr_ref);
	else if (key == XK_d)
		ifctx->node_attr_ref = cycle_sel_attr(sel_prim, ifctx->node_attr_ref);
	else if (key == XK_w)
		*ifctx->node_attr_ref += 1.5f;
	else if (key == XK_s)
		*ifctx->node_attr_ref = fmax(*ifctx->node_attr_ref - 1.f, 0.f);
}

//static void	toggle_interface(t_ifctx * const ifctx)
//{
//	ifctx->visible = !ifctx->visible;
//}

static void	cycle_if_mode(t_ifctx * const ifctx)
{
	if (++ifctx->mode > IF_MODE_LAST)
		ifctx->mode = IF_MODE_FIRST;
}

static void	poll_obj_sel(const int key, t_ifctx *ifctx)
{
	if (key == XK_q)
		--ifctx->node_index;
	else if (key == XK_e)
		++ifctx->node_index;
	ifctx->node_index = clamp(ifctx->node_index, 0, ifctx->rtctx->node_n - 1);
	ifctx->node_attr_ref = NULL;
}

void	poll_interface(const int key, t_rtctx *rtctx)
{
	if (key == XK_f)
		cycle_if_mode(&rtctx->ifctx);
	if (rtctx->ifctx.mode == IF_MODE_TRANSLATE)
		poll_translate(key, &rtctx->ifctx);
	if (rtctx->ifctx.mode == IF_MODE_ROTATE)
		printf("Im rotating\n");//poll_rotate(key, ifctx);
	if (rtctx->ifctx.mode == IF_MODE_MORPH)
		poll_prim_morph(key, &rtctx->ifctx);
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
	char * const	mode_names[] = {"Translate", "Rotate", "Reshape"};
	char * const	obj_types[] = {"Camera", "Light", "Primitive"};
	char * const	prim_names[] = {"Plane", "Sphere", "Cylinder"};
	char		*status_str;

	if (!ifctx->visible)
		return ;
	status_str = ft_strjoin("MODE: ", mode_names[ifctx->mode]);
	ft_strjoin_morph(&status_str, " | OBJECT TYPE: ");
	ft_strjoin_morph(&status_str, obj_types[if_get_sel_node(ifctx)->type]);
	if (ifctx->node_attr_ref)
	{
		ft_strjoin_morph(&status_str, " | ATTRIBUTE: ");
		ft_strjoin_morph(&status_str,get_prim_attr_name(if_get_sel_node(ifctx), ifctx->node_attr_ref));
	}
	if (if_get_sel_node(ifctx)->type == NODE_PRIM)
	{
		ft_strjoin_morph(&status_str, " | PRIMITIVE TYPE: ");
		ft_strjoin_morph(&status_str, prim_names[((t_primitive *)if_get_sel_node(ifctx))->type]);
	}
	mlx_string_put(ifctx->rtctx->mlx_ptr, ifctx->rtctx->window_ptr, 20, 20, (1 << 24) - 1, status_str);
	free(status_str);
}
