/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraTransform.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:05:41 by joaoteix          #+#    #+#             */
/*   Updated: 2024/01/31 17:54:16 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERATRANSFORM_H
# define CAMERATRANSFORM_H

#include "Transform.h"

//	Render space corresponds to camera-world space in this implementation
//	Camera-world space is the space centered at the camera's position
//	and oriented the same as the world

typedef s_CameraTransform {
	t_Transform	renderFromCamera;
	t_Transform	worldfromRender;
}	t_CameraTransform;

void		CameraTransformInit(t_CameraTransform *camTransform, t_Transform worldFromCamera);

t_Point3f		RenderFromCamera(t_Point3f p) const;
t_Point3f		CameraFromRender(t_Point3f p) const;
t_Point3f		RenderFromWorldP3(t_Point3f p) const;
t_Transform		RenderFromWorld(void) const;
t_Transform		CameraFromWorld(void) const;
t_Transform		CameraFromRender(void) const;

#endif
