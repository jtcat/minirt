/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:18:33 by joaoteix          #+#    #+#             */
/*   Updated: 2024/02/03 17:01:44 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vec3.h"

typedef s_camera {
	int		image_width;
	int		image_height;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	double	hfov;
	vec3	lookfrom;
	vec3	lookat;
	vec3	pix_ul_p;
	vec3	pix_du;
	vec3	pix_dv;
	vec3	u; 
	vec3	v; 
	vec3	w; 
}	t_camera

void	cam_init(t_camera *cam);
void	render(t_camera *cam);

#endif
