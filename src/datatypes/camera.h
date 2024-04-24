/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:18:33 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/24 12:09:57 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "node3d.h"
# include "vec3.h"
# include "utils.h"

// Inherits node3d
typedef struct s_camera {
	t_node3d	node;
	int			image_width;
	int			image_height;
	double		aspect_ratio;
	double		focal_length;
	double		viewport_width;
	double		viewport_height;
	float		hfov;
	t_vec3		lookfrom;
	t_vec3		lookdir;
	t_vec3		pix_ul_p;
	t_vec3		pix_du;
	t_vec3		pix_dv;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
}	t_camera;

void	cam_init(t_camera *cam);

#endif
