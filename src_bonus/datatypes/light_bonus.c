/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:47:17 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:01:35 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_bonus.h"

t_light	*light_new(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light)
		light->node.type = NODE_LIGHT;
	return (light);
}
