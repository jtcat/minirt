/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:17:10 by jcat              #+#    #+#             */
/*   Updated: 2024/04/04 21:49:08 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "vec3.h"

void	free_ptrarr(void **arr);

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal);

void	print_err(char *msg);

float	fsign(float f);

int	tern(int cond, int a, int b);

int	clamp(int a, int min, int max);
#endif
