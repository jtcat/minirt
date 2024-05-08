/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_utils_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:02:03 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 16:11:16 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IF_UTILS_BONUS_H
# define IF_UTILS_BONUS_H

# include <stdbool.h>
# include "X11/keysym.h"

# define IF_MODE_FIRST IF_MODE_TRANSLATE
# define IF_MODE_LAST IF_MODE_MORPH

typedef struct s_rtctx	t_rtctx;

enum e_ifmode
{
	IF_MODE_TRANSLATE,
	IF_MODE_ROTATE,
	IF_MODE_MORPH
};

typedef struct s_ifctx
{
	t_rtctx			*rtctx;
	enum e_ifmode	mode;
	bool			visible;
	int				node_index;
	double			*node_attr_ref;
}	t_ifctx;

#endif
