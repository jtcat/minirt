/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:18:33 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:12:30 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "node3d_bonus.h"
# include "vec3_bonus.h"
# include "../utils_bonus.h"

// Inherits node3d

typedef struct s_camera
{
	t_node3d	node;
	int			image_width;
	int			image_height;
	double		aspect_ratio;
	double		focal_length;
	double		viewport_width;
	double		viewport_height;
	double		hfov;
	t_vec3		pos;
	t_vec3		pix_ul_p;
	t_vec3		pix_du;
	t_vec3		pix_dv;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
}	t_camera;

void	cam_init(t_camera *cam);
void	cam_calcviewport(t_camera *cam);

#endif
