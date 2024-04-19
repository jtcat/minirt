/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:18:33 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/18 16:14:41 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec3.h"
# include "utils.h"

typedef struct s_camera
{
	int		image_width;
	int		image_height;
	double	aspect_ratio;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	float	hfov;
	t_vec3	lookfrom;
	t_vec3	lookdir;
	t_vec3	pix_ul_p;
	t_vec3	pix_du;
	t_vec3	pix_dv;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}	t_camera;

void	cam_init(t_camera *cam);

#endif
