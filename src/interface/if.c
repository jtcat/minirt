/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:59:30 by jcat              #+#    #+#             */
/*   Updated: 2024/04/19 15:10:41 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/rt.h"
#include "if.h"

static const char	*get_prim_attr_name(const t_obj *obj, void *attrib_ptr)
{
	if (obj->type == RT_PRIM_SPHERE)
		if (attrib_ptr == &((t_sphere *)obj->spec)->radius)
			return ("Radius");
	if (obj->type == RT_PRIM_CYLINDER)
	{
		if (attrib_ptr == &((t_cylinder *)obj->spec)->h)
			return ("Height");
		if (attrib_ptr == &((t_cylinder *)obj->spec)->r)
			return ("Radius");
	}
}

static void	*cycle_obj_attr(const t_obj *obj, void *curr_attr)
{
	if (obj->type == RT_PRIM_SPHERE)
		return (&((t_sphere *)obj->spec)->radius);
	if (obj->type == RT_PRIM_CYLINDER)
	{
		if (curr_attr == &((t_cylinder *)obj->spec)->h)
			return (&((t_cylinder *)obj->spec)->r);
		return (&((t_cylinder *)obj->spec)->h);
	}
}

static void	poll_rotate(const int key, t_ifctx * const ifctx)
{
	t_transf	rot_mat;

	// W and S rotate around object X-Axis
	// A and D rotate around object Z-Axis
	transform_apply(&ifctx->sel_obj->transf, &rot_mat);
}

static void	poll_translate(const int key, t_ifctx * const ifctx)
{
	const t_vec3	pos = {(key == XK_D) - (key == XK_A),
					(key == XK_space) - (key == XK_Control_L),
					(key == XK_W) - (key == XK_S)};
	t_transf		transl;

	tf_from_pos(&pos, &transl);
	transform_apply(&ifctx->sel_obj->transf, &transl);
}

static void	poll_resize(const int key, t_rtctx * const rtctx)
{
	t_ifctx *const	ifctx = &rtctx->ifctx;
	t_obj *const	obj = get_if_obj_sel(ifctx);

	if (key == XK_D)
		ifctx->obj_attr_ref = cycle_obj_attr(get_if_obj_sel(ifctx));
	else if (key == XK_A)
		ifctx->obj_attr_ref = fmax(*ifctx->obj_attr_ref - 1, 0);
	else if (key == XK_W)
		*ifctx->obj_attr_ref += 1.f;
	else if (key == XK_S)
		*ifctx->obj_attr_ref = fmax(*ifctx->obj_attr_ref - 1.f, 0.f);
}

static void	toggle_interface(t_ifctx * const ifctx)
{
	ifctx->visible = !ifctx->visible;
}

static void	cycle_if_mode(t_ifctx * const ifctx)
{
	if (++ifctx->mode > IF_MODE_LAST)
		ifctx->mode = IF_MODE_FIRST;
}

static void	poll_obj_sel(const int key, t_rtctx * const rtctx)
{
	t_ifctx *const	ifctx = &rtctx->ifctx;

	if (key == XK_Q)
		--ifctx->sel_obj_index;
	else if (key == XK_E)
		++ifctx->sel_obj_index;
	ifctx->sel_obj_index = clamp(ifctx->sel_obj_index, 0, rtctx->obj_n);
	ifctx->obj_attr_ref = NULL;
}

void	poll_interface(const int key, t_rtctx * const ctx)
{
	if (key == XK_h)
		toggle_interface(&ctx->ifctx);
	else if (key == XK_f)
		cycle_if_mode(&ctx->ifctx);
	else if (ctx->ifctx.mode == IF_TRANSLATE)
		poll_translate(key, &ctx->ifctx);
	else if (ctx->ifctx.mode == IF_ROTATE)
		poll_rotate(key, &ctx->ifctx);
	else if (ctx->ifctx.mode == IF_RESIZE)
		poll_resize(key, ctx);
	else
	 	poll_obj_sel(key, ctx);
}

void	display_interface(t_rtctx * const ctx)
{
	char * const	mode_names[] = {"Translate", "Rotate", "Reshape"};
	char * const	obj_types[] = {"Camera", "Light", "Plane", "Sphere", "Cylinder"};
	char			*status_str;
	char			*tmp;

	if (!ctx->ifctx.visible)
		return ;
	status_str = ft_strjoin("MODE: ", mode_names[ctx->ifctx->mode]);
	ft_strjoin_morph(&status_str, "\nOBJECT TYPE: ");
	ft_strjoin_morph(&status_str, obj_types[get_if_obj_sel(ctx->ifctx)->type]);
	ft_strjoin_morph(&status_str, "\nATTRIBUTE: ");
	ft_strjoin_morph(&status_str, tmp);
	free(tmp);
	tmp = get_prim_attr_name(get_if_obj_sel(ctx->ifctx));
	ft_strjoin_morph(&status_str, tmp);
	free(tmp);
	mlx_string_put(ctx->mlx_ptr, ctx->window_ptr, 20, 20, (1 << 24) - 1, status_str);
	free(status_str);
}
