/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:17:10 by jcat              #+#    #+#             */
/*   Updated: 2024/04/01 00:09:42 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "vec3.h"

double	deg_to_rad(const double deg);

void	free_ptrarr(void **arr);

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal);

void	print_err(char *msg);
#endif
