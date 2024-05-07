/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim_construct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 23:09:36 by jcat              #+#    #+#             */
/*   Updated: 2024/05/07 15:21:25 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

t_plane	*plane_new(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane)
	{
		plane->prim.node.type = NODE_PRIM;
		plane->prim.type = PRIM_PLANE;
		plane->prim.intersect = i_plane;
	}
	return (plane);
}

t_sphere	*sphere_new(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere)
	{
		sphere->prim.node.type = NODE_PRIM;
		sphere->prim.type = PRIM_SPHERE;
		sphere->prim.intersect = i_sphere;
	}
	return (sphere);
}

t_cylinder	*cylinder_new(void)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder)
	{
		cylinder->prim.node.type = NODE_PRIM;
		cylinder->prim.type = PRIM_CYLINDER;
		cylinder->prim.intersect = i_cylinder;
	}
	return (cylinder);
}
