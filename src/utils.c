/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:10:12 by jcat              #+#    #+#             */
/*   Updated: 2024/05/05 16:53:21 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "unistd.h"

double	ftern(int cond, double a, double b)
{
	return ((double)cond * a + (double) !cond * b);
}

double	fsign(double f)
{
	return ((f > 0.0f) - (f < 0.0f));
}

static inline double	fsel(double a, double b, double c)
{
	return (ftern(a >= 0.f, b, c));
}

int	clamp(int a, int min, int max)
{
	a = fsel(a - min, a, min);
	return (fsel(a - max, max, a));
}

double	fclamp(double a, double min, double max)
{
	a = fsel(a - min, a, min);
	return (fsel(a - max, max, a));
}
