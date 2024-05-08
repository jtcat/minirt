/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:59:30 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 16:48:00 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt.h"
#include "if_utils.h"
#include "if.h"

#define CAM_ROT_STEP .2f

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

static inline void	set_node_rot_mat(t_node3d *node, t_transf *rot, double yang)
{
	if (node->type == NODE_CAM)
	{
		rot->mat[0][0] = cos(yang);
		rot->mat[0][2] = sin(yang);
		rot->mat[2][0] = -sin(yang);
		rot->mat[2][2] = cos(yang);
	}
	else
	{
		rot->mat[0][0] = cos(yang);
		rot->mat[0][1] = -sin(yang);
		rot->mat[1][0] = sin(yang);
		rot->mat[1][1] = cos(yang);
	}
}

void	poll_rotate(const int key, t_ifctx *ifctx)
{
	t_node3d *const	node = if_get_sel_node(ifctx);
	t_transf		rot;
	double			yang;
	double			xang;

	yang = (-(key == XK_a) + (key == XK_d)) * CAM_ROT_STEP;
	xang = (-(key == XK_w) + (key == XK_s)) * CAM_ROT_STEP;
	ft_identity(&rot);
	set_node_rot_mat(node, &rot, yang);
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

void	poll_translate(const int key, t_ifctx *const ifctx)
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

void	poll_node_morph(const int key, t_ifctx *ifctx)
{
	t_node3d *const		sel_node = if_get_sel_node(ifctx);

	if (key == XK_a)
		ifctx->node_attr_ref = cycle_sel_attr(sel_node, ifctx->node_attr_ref);
	else if (key == XK_d)
		ifctx->node_attr_ref = cycle_sel_attr(sel_node, ifctx->node_attr_ref);
	if (ifctx->node_attr_ref)
	{
		if (key == XK_w)
			*ifctx->node_attr_ref += 1.5f;
		if (key == XK_s)
			*ifctx->node_attr_ref = fmax((*ifctx->node_attr_ref) - 1.5f, 0.f);
	}
}
