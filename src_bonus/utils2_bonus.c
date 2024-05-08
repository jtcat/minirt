/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:44:14 by psotto-m          #+#    #+#             */
/*   Updated: 2024/05/08 13:52:29 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "datatypes/vec3_bonus.h"
#include "utils_bonus.h"
#include "render/rt_bonus.h"
#include "parser/parser_bonus.h"

t_vec3	perf_ray(t_vec3 *ldir, t_vec3 *normal)
{
	return (v3sub(v3scalef(*normal, 2 * v3dot(*ldir, *normal)), *ldir));
}

void	arg_val(int argc, char **argv)
{
	if (argc != 2)
	{
		print_err("Incorrect number of arguments");
		exit(1);
	}
	if (ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) == NULL)
	{
		print_err("File must have an '.rt' extension");
		exit(1);
	}
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	free_ptrarr(void **arr)
{
	void	**iter;

	if (!arr)
		return ;
	iter = arr;
	while (*iter)
	{
		free(*iter);
		iter++;
	}
	free(arr);
}

void	ft_strjoin_morph(char **dst, char *join)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, join);
	free(*dst);
	*dst = tmp;
}
