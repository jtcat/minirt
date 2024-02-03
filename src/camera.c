/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:35:10 by joaoteix          #+#    #+#             */
/*   Updated: 2024/02/03 18:34:59 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"
#include <stdio.h>

void	cam_init(t_camera *cam)
{
	vec3	viewport_u;
   	vec3	viewport_v;
	vec3	viewport_ul;

	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 600;
	image_height = image_width / aspect_ratio;
	cam->focal_length = 1.0;
	cam->viewport_width = 2 * tan(deg_to_rad(cam->hfov) / 2) * cam->focal_length;
	cam->viewport_height = viewport_width / ((double)(image_width) / image_height);
	cam->w = unit(cam->lookat);
	cam->u = unit(cross(vec3_new(0,1,0));
	cam->v = cross(w, u);
	viewport_u	= v3scalef(u, viewport_width);
	viewport_v	= v3scalef(v, -viewport_width);
	cam->pix_du = v3scalef(viewport_u, 1 / cam->image_width);
	cam->pix_dv = v3scalef(viewport_v, 1 / cam->image_height);
	viewport_ul = v3subtract(v3subtract(cam->lookfrom, v3scalef(w, cam->focal_length)), v3scalef(v3subtract(viewport_u, viewport_v), 0.5));
	pix_ul_p = v3sum(v3sum(viewport_ul, v3scalef(v3sum(pix_du, pix_dv), 0.5)));
}

void	render(t_rtctx *ctx, t_camera *cam)
{
	int		i;
	int		j;
	vec3	pix_center;
	vec3	ray_dir;

	printf("Image width: %d, Image height: %d\n", cam->image_width, cam->image_height);
	i = 0;
	while (i < image_height)
	{
		j = 0;
		while (j < image_width)
		{
			pix_center = v3sum(vec3sum(cam->pix_ul_p, v3scale(pix_du, i)), v3scale(pix_dv, j));
			ray_dir = v3subtract(pix_center, cam->lookfrom);

			image[i][j] = trace(t_rtctx *ctx, pix_center, ray_dir);
			j++;
		}
		i++;
	}
}
