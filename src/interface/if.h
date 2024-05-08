/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:53:57 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 10:19:10 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IF_H
# define IF_H

# include "if_utils.h"
# include "../render/rt.h"

void		ifctx_init(t_ifctx *ifctx, t_rtctx *ctx);
void		poll_interface(const int key, t_rtctx *rtctx);
void		display_interface(const t_ifctx *ifctx);

t_node3d	*if_get_sel_node(const t_ifctx *ifctx);
void		*cycle_sel_attr(const t_node3d *node, void *curr_attr);
void		poll_translate(const int key, t_ifctx *const ifctx);
void		poll_rotate(const int key, t_ifctx *ifctx);
void		poll_node_morph(const int key, t_ifctx *ifctx);
void		poll_obj_sel(const int key, t_ifctx *ifctx);

#endif
