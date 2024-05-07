/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:53:57 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/07 15:04:16 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IF_H
# define IF_H

# include "if_utils.h"

void	ifctx_init(t_ifctx *ifctx, t_rtctx *ctx);
void	poll_interface(const int key, t_rtctx *rtctx);
void	display_interface(const t_ifctx *ifctx);

#endif
