/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:17:10 by jcat              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/18 15:57:01 by psotto-m         ###   ########.fr       */
=======
/*   Updated: 2024/04/19 15:02:52 by jcat             ###   ########.fr       */
>>>>>>> 7f4ccd7 (first interface logic and refactor)
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <libft.h>
# include "datatypes/vec3.h"

void	free_ptrarr(void **arr);

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal);

void	print_err(char *msg);

float	fsign(float f);

int		tern(int cond, int a, int b);

float	ftern(int cond, float a, float b);

int		clamp(int a, int min, int max);
float	fclamp(float a, float min, float max);
int		key_handler(int keycode, void *params);
void	arg_val(int argc, char **argv);

void	ft_strjoin_morph(char **dst, const char *other);
#endif
