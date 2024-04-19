/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:25:20 by psotto-m          #+#    #+#             */
/*   Updated: 2024/04/19 14:25:24 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../datatypes/vec3.h"
#include "primitives.h"

void	prim_destroy(void *vprim)
{
	t_primitive	*prim;

	prim = (t_primitive *)vprim;
	if (prim->spec)
		free(prim->spec);
	free(prim);
}
