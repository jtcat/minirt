/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:17:10 by jcat              #+#    #+#             */
/*   Updated: 2024/05/08 13:53:24 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <libft.h>
# include "datatypes/vec3_bonus.h"

void	free_ptrarr(void **arr);

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal);

void	print_err(char *msg);

double	fsign(double f);

int		tern(int cond, int a, int b);

double	ftern(int cond, double a, double b);

int		clamp(int a, int min, int max);
double	fclamp(double a, double min, double max);
void	arg_val(int argc, char **argv);

void	ft_strjoin_morph(char **dst, char *other);
#endif
