/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:35:10 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/01 02:49:30 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	cam_init(t_camera *cam)
{
	const t_vec3	v3_up = {0, 1.0, 0};
	t_vec3			viewport_u;
	t_vec3			viewport_v;
	t_vec3			viewport_ul;

	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 600;
	cam->image_height = cam->image_width / cam->aspect_ratio;
	cam->focal_length = 1.0;
	cam->viewport_width = 2 * tan(deg_to_rad(cam->hfov) / 2)
		* cam->focal_length;
	cam->viewport_height = cam->viewport_width
		/ ((double)(cam->image_width) / cam->image_height);
	cam->w = v3unit(v3sub(cam->lookdir, cam->lookdir));
	cam->u = v3unit(v3cross(v3_up, cam->w));
	cam->v = v3cross(cam->w, cam->u);
	viewport_u = v3scalef(cam->u, cam->viewport_width);
	viewport_v = v3scalef(cam->v, -cam->viewport_width);
	cam->pix_du = v3scalef(viewport_u, 1.0 / cam->image_width);
	cam->pix_dv = v3scalef(viewport_v, 1.0 / cam->image_height);
	viewport_ul = v3sub(v3sub(cam->lookfrom, v3scalef(cam->w, \
			cam->focal_length)), v3scalef(v3sub(viewport_u, viewport_v), 0.5));
	cam->pix_ul_p = v3sum(viewport_ul,
			v3scalef(v3sum(cam->pix_du, cam->pix_dv), 0.5));
}
