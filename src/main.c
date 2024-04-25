/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:54:56 by jcat              #+#    #+#             */
/*   Updated: 2024/04/25 17:52:43 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "render/rt.h"
#include "parser/parser.h"
#include "utils.h"
#include "interface/if.h"

int	expose_handler(t_rtctx *ctx)
{
	render(ctx);
	display(ctx, &ctx->img);
	return (1);
}

void	create_window(t_rtctx *ctx)
{
	ctx->window_ptr = mlx_new_window(ctx->mlx_ptr,
			ctx->cam.image_width,
			ctx->cam.image_height, WINDOW_TITLE);
	ctx->img.img_ptr = mlx_new_image(ctx->mlx_ptr, \
			ctx->cam.image_width, ctx->cam.image_height);
	ctx->img.img_addr = mlx_get_data_addr(ctx->img.img_ptr,
			&ctx->img.color_depth, &ctx->img.line_len, &ctx->img.endian);
}

int	render_run(t_rtctx *ctx)
{
	cam_init(&ctx->cam);
	ctx->mlx_ptr = mlx_init();
	create_window(ctx);
	mlx_key_hook(ctx->window_ptr, &key_handler, ctx);
	mlx_hook(ctx->window_ptr, DESTROY_NOTIFY, 0, &mlx_loop_end, ctx->mlx_ptr);
	mlx_expose_hook(ctx->window_ptr, expose_handler, ctx);
	mlx_loop(ctx->mlx_ptr);
	cleanup_mlx(ctx);
	return (0);
}

bool	validate_scene(t_rtctx *ctx)
{
	if (ctx->cam.hfov == -1)
	{
		print_err("No camera present");
		return (false);
	}
	if (ctx->ambient.r == -1)
	{
		print_err("No ambient light defined");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_rtctx	rtctx;

	arg_val(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		print_err("Cannot open file");
		exit(1);
	}
	rtctx_init(&rtctx);
	if (!parser_main(&rtctx, fd) || !validate_scene(&rtctx))
	{
		rtctx_destroy(&rtctx);
		return (1);
	}
	ifctx_init(&rtctx.ifctx, &rtctx);
	make_node_ref_list(&rtctx);
	render_run(&rtctx);
	rtctx_destroy(&rtctx);
	return (0);
}
