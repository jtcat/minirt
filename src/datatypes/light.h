/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:46:12 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/24 09:47:55 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "node3d.h"
# include "argb.h"

// Inherits node3d
typedef struct s_light
{
	t_node3d	node;
	t_color3	color;
	float		f;
}	t_light;

t_light	*light_new(void);
#endif
