/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:10:12 by jcat              #+#    #+#             */
/*   Updated: 2024/04/07 00:39:50 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "unistd.h"

int	tern(int cond, int a, int b)
{
	return (cond * a + !cond * b);
}

float	fsign(float f)
{
	return ((f > 0.0f) - (f < 0.0f));
}

static inline int	fsel(int a, int b, int c)
{
	return (tern(a >= 0, b, c));
}

int	clamp(int a, int min, int max)
{
	a = fsel(a - min, a, min);
	return (fsel(a - max, max, a));
}

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
	return (v3sub(v3scalef(*normal, 2 * v3dot(*ldir, *normal)), *ldir));
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
