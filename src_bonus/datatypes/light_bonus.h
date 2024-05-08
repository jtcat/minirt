/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:46:12 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:01:45 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

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
