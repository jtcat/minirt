/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:59:30 by jcat              #+#    #+#             */
/*   Updated: 2024/05/05 16:49:24 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt.h"
#include "if_utils.h"
#include <stdio.h>

#define CAM_ROT_STEP .2f

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

static void	*cycle_sel_attr(const t_node3d *node, void *curr_attr)
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

void	ft_identity(t_transf *t)
{
	t->mat[0][0] = 1;	
	t->mat[0][1] = 0;	
	t->mat[0][2] = 0;	
	t->mat[0][3] = 0;	
	t->mat[1][0] = 0;	
	t->mat[1][1] = 1;	
	t->mat[1][2] = 0;	
	t->mat[1][3] = 0;	
	t->mat[2][0] = 0;	
	t->mat[2][1] = 0;	
	t->mat[2][2] = 1;	
	t->mat[2][3] = 0;	
	t->mat[3][0] = 0;	
	t->mat[3][1] = 0;	
	t->mat[3][2] = 0;	
	t->mat[3][3] = 1;	
}

static void	poll_rotate(const int key, t_ifctx *ifctx)
{
	t_node3d *const	node = if_get_sel_node(ifctx);
	t_transf		rot;
	float			yang;
	float			xang;

	yang = (-(key == XK_a) + (key == XK_d)) * CAM_ROT_STEP;
	xang = (-(key == XK_w) + (key == XK_s)) * CAM_ROT_STEP;
	ft_identity(&rot);
	if (node->type == NODE_CAM)
	{
		rot.mat[0][0] = cos(yang);
		rot.mat[0][2] = sin(yang);
		rot.mat[2][0] = -sin(yang);
		rot.mat[2][2] = cos(yang);
	}
	else
	{
		rot.mat[0][0] = cos(yang);
		rot.mat[0][1] = -sin(yang);
		rot.mat[1][0] = sin(yang);
		rot.mat[1][1] = cos(yang);
	}
	tf_transform(&node->transf, &rot, &node->transf);
	ft_identity(&rot);
	rot.mat[1][1] = cos(xang);
	rot.mat[1][2] = -sin(xang);
	rot.mat[2][1] = sin(xang);
	rot.mat[2][2] = cos(xang);
	tf_transform(&node->transf, &rot, &node->transf);
	if (node->type == NODE_CAM)
		cam_calcviewport(&ifctx->rtctx->cam);
}

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
		tf_transform(&transf, &node->transf, &node->transf);
		cam_calcviewport(&ifctx->rtctx->cam);
	}
	else
		tf_translate(&node->transf, &transl);
}

static void	poll_node_morph(const int key, t_ifctx *ifctx)
{
	t_node3d *const		sel_node = if_get_sel_node(ifctx);

	if (!ifctx->node_attr_ref)
		return ;
	if (key == XK_a)
		ifctx->node_attr_ref = cycle_sel_attr(sel_node, ifctx->node_attr_ref);
	else if (key == XK_d)
		ifctx->node_attr_ref = cycle_sel_attr(sel_node, ifctx->node_attr_ref);
	else if (key == XK_w)
		*ifctx->node_attr_ref += 1.5f;
	else if (key == XK_s)
		*ifctx->node_attr_ref = fmax(*ifctx->node_attr_ref - 1.5f, 0.f);
	if (sel_node->type == NODE_CAM)
		cam_calcviewport(&ifctx->rtctx->cam);
}

static void	cycle_if_mode(t_ifctx * const ifctx)
{
	if (++ifctx->mode > IF_MODE_LAST)
		ifctx->mode = IF_MODE_FIRST;
}

static void	poll_obj_sel(const int key, t_ifctx *ifctx)
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
	char * const	mode_names[] = {"Translate", "Rotate", "Morph"};
	char * const	obj_types[] = {"Camera", "Light", "Primitive"};
	char * const	prim_names[] = {"Plane", "Sphere", "Cylinder"};
	char		*status_str;

	if (!ifctx->visible)
		return ;
	status_str = ft_strjoin("MODE: ", mode_names[ifctx->mode]);
	ft_strjoin_morph(&status_str, " | OBJECT TYPE: ");
	ft_strjoin_morph(&status_str, obj_types[if_get_sel_node(ifctx)->type]);
	if (if_get_sel_node(ifctx)->type == NODE_PRIM)
	{
		ft_strjoin_morph(&status_str, " | PRIMITIVE TYPE: ");
		ft_strjoin_morph(&status_str, prim_names[((t_primitive *)if_get_sel_node(ifctx))->type]);
	}
	if (ifctx->node_attr_ref)
	{
		ft_strjoin_morph(&status_str, " | ATTRIBUTE: ");
		ft_strjoin_morph(&status_str,get_prim_attr_name(if_get_sel_node(ifctx), ifctx->node_attr_ref));
	}
	mlx_string_put(ifctx->rtctx->mlx_ptr, ifctx->rtctx->window_ptr, 20, 20, (1 << 24) - 1, status_str);
	free(status_str);
}
