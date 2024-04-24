/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:44:14 by psotto-m          #+#    #+#             */
/*   Updated: 2024/04/24 12:10:57 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "unistd.h"
#include <stdlib.h>
#include <libft.h>
#include "datatypes/vec3.h"
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "render/rt.h"
#include "parser/parser.h"

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

int	key_handler(int keycode, t_rtctx *ctx)
{
	if (keycode == XK_Escape)
		mlx_loop_end(ctx->mlx_ptr);
//	else
//	 	poll_interface(keycode, ctx);
	return (1);
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
