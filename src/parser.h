/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcat <joaoteix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:53:06 by jcat              #+#    #+#             */
/*   Updated: 2024/03/31 23:56:56 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "rt.h"
#include "utils.h"
#include "../gnl/get_next_line_bonus.h"
#include "../libft/libft.h"
#include <stdbool.h>

bool	parser_main(t_rtctx *ctx, int fd);

bool (parse_ambient(t_rtctx *ctx, char **tokens));
bool (parse_camera(t_rtctx *ctx, char **tokens));
bool (parse_light(t_rtctx *ctx, char **tokens));
bool (parse_sphere(t_rtctx *ctx, char **tokens));
bool (parse_plane(t_rtctx *ctx, char **tokens));
bool (parse_cylinder(t_rtctx *ctx, char **tokens));

#endif

