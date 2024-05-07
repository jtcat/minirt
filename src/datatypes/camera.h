/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:18:33 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/07 14:50:57 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "node3d.h"
# include "vec3.h"
# include "utils.h"

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
