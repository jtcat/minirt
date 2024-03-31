/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:54:56 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 23:52:57 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "rt.h"
#include "parser.h"


int	main(int argc, char **argv)
{
	int	fd;
	t_rtctx	ctx;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "minirt: incorrect number of arguments\n");
		return (1);
	}
	if (ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minirt: file must have an '.rt' extension\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_err("Cannot open file\n");
	if (!parse_main(&ctx, fd))
		return (1);
	rt_main(&ctx);
	return (0);
}
