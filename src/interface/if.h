/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:02:03 by jcat              #+#    #+#             */
/*   Updated: 2024/04/19 14:45:13 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IF_H
# define IF_H

#include <stdbool.h>
#include "X11/keysym.h"
#include "../datatypes/matrix.h"

# define IF_MODE_FIRST IF_TRANSLATE
# define IF_MODE_LAST IF_RESIZE

enum e_ifmode {IF_TRANSLATE, IF_ROTATE, IF_RESIZE};

typedef struct s_ifctx
{
	enum e_ifmode	mode;
	bool			visible;
	int				sel_obj_index;
	float			*obj_attr_ref;
}	t_ifctx;

void	poll_interface(const int key, t_rtctx * const ctx)

#endif
