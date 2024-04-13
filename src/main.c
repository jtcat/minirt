/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:54:56 by jcat              #+#    #+#             */
/*   Updated: 2024/04/07 00:13:45 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include "render/rt.h"
#include "parser/parser.h"

int	key_handler(int keycode, void *params)
{
	if (keycode == XK_Escape)
		mlx_loop_end(params);
	return (1);
}

void	create_window(t_rtctx *ctx)
{
	ctx->window_ptr = mlx_new_window(ctx->mlx_ptr,
			ctx->cam.image_width,
			ctx->cam.image_height, WINDOW_TITLE);
	ctx->img.img_ptr = mlx_new_image(ctx->mlx_ptr, ctx->cam.image_width, ctx->cam.image_height);
	ctx->img.img_addr = mlx_get_data_addr(ctx->img.img_ptr,
			&ctx->img.color_depth, &ctx->img.line_len, &ctx->img.endian);
}

int	render_main(t_rtctx *ctx)
{
	cam_init(&ctx->cam);
	ctx->mlx_ptr = mlx_init();
	create_window(ctx);
	mlx_key_hook(ctx->window_ptr, &key_handler, ctx->mlx_ptr);
	mlx_hook(ctx->window_ptr, DESTROY_NOTIFY, 0, &mlx_loop_end, ctx->mlx_ptr);
	render(ctx);
	mlx_loop(ctx->mlx_ptr);
	cleanup_mlx(ctx);
	return (0);
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

bool validate_scene(t_rtctx *ctx)
{
	if(ctx->cam.hfov == -1)
	{
		print_err("No Camera present");
		return (false);
	}
	if(ctx->light.f == -1)
	{
		print_err("No Light present");
		return (false);
	}	
	if(ctx->ambient.r == -1)
	{
		print_err("No Ambient Light present");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_rtctx	ctx;

	arg_val(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		print_err("Cannot open file");
		exit(1);
	}
	rtctx_init(&ctx);
	if (!parser_main(&ctx, fd) || !validate_scene(&ctx))
	{
		rtctx_destroy(&ctx);
		return (1);
	}
	render_main(&ctx);
	rtctx_destroy(&ctx);
	return (0);
}
