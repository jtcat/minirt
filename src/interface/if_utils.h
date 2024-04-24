/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:02:03 by jcat              #+#    #+#             */
/*   Updated: 2024/04/23 15:39:14 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IF_UTILS_H
# define IF_UTILS_H

#include <stdbool.h>
#include "X11/keysym.h"
#include "../render/rt.h"

# define IF_MODE_FIRST IF_TRANSLATE
# define IF_MODE_LAST IF_RESIZE

enum e_ifmode {IF_TRANSLATE, IF_ROTATE, IF_RESIZE};

typedef struct s_ifctx
{
	t_rtctx			*rtctx;
	enum e_ifmode	mode;
	bool			visible;
	int				node_index;
	float			*obj_attr_ref;
}	t_ifctx;

#endif
