/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:53:06 by jcat              #+#    #+#             */
/*   Updated: 2024/04/04 00:04:28 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "rt.h"
#include "utils.h"
#include "../gnl/gnl.h"
#include "../libft/libft.h"
#include <stdbool.h>

bool	parse_float(const char *str, float* f);
bool	parse_int(const char *str, int* f);
bool	parse_vec3(const char *str, t_vec3* f);
bool	parse_rgb(const char *str, t_argb* f);

bool	parser_main(t_rtctx *ctx, int fd);

char	**parse_ambient(t_rtctx *ctx, char **tokens);
char	**parse_camera(t_rtctx *ctx, char **tokens);
char	**parse_light(t_rtctx *ctx, char **tokens);
char	**parse_sphere(t_rtctx *ctx, char **tokens);
char	**parse_plane(t_rtctx *ctx, char **tokens);
char	**parse_cylinder(t_rtctx *ctx, char **tokens);

#endif

