/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:10:12 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 23:41:45 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_ptrarr(void **arr)
{
	void	**iter;
	
	if(!arr)
		return ;
	iter = arr;
	while (*iter)
	{
		free(*iter);
		iter++;
	}
	free(arr);
}

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal)
{
	return (v3sub(v3scalef(*normal, 2 * v3dot(*ldir, *normal)), *normal));
}
