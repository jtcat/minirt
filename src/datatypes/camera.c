/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:35:10 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/26 19:14:29 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static inline bool	v3iszero(t_vec3 v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

void	cam_calcviewport(t_camera *cam)
{
	t_vec3			viewport_u;
	t_vec3			viewport_v;
	t_vec3			viewport_ul;

	cam->u = tf_get_vec(&cam->node.transf, 0);
	cam->v = tf_get_vec(&cam->node.transf, 1);
	cam->w = tf_get_vec(&cam->node.transf, 2);
	cam->pos = tf_get_vec(&cam->node.transf, 3);
	cam->viewport_width = 2.0f * tan(cam->hfov / 2.0f) * cam->focal_length;
	cam->viewport_height = cam->viewport_width / cam->aspect_ratio;
	viewport_u = v3scalef(cam->u, cam->viewport_width);
	viewport_v = v3scalef(cam->v, -cam->viewport_height);
	cam->pix_du = v3scalef(viewport_u, 1.0 / cam->image_width);
	cam->pix_dv = v3scalef(viewport_v, 1.0 / cam->image_height);
	viewport_ul = v3sub(v3sum(cam->pos, v3scalef(cam->w, \
			cam->focal_length)), v3scalef(v3sum(viewport_u, viewport_v), 0.5));
	cam->pix_ul_p = v3sum(viewport_ul,
			v3scalef(v3sum(cam->pix_du, cam->pix_dv), 0.5));
}

void	cam_init(t_camera *cam)
{
	cam->node.type = NODE_CAM;
	cam->focal_length = 1.0f;
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 1300;
	cam->image_height = cam->image_width / cam->aspect_ratio;
	tf_look_along(&cam->pos, cam->w, &cam->node.transf);
	cam_calcviewport(cam);
}
