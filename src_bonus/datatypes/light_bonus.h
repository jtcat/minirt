/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:46:12 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 15:07:30 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_BONUS_H
# define LIGHT_BONUS_H

# include "node3d_bonus.h"
# include "argb_bonus.h"

// Inherits node3d
typedef struct s_light
{
	t_node3d	node;
	t_color3	color;
	double		f;
}	t_light;

t_light	*light_new(void);
#endif
