/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraTransform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:37:39 by joaoteix          #+#    #+#             */
/*   Updated: 2024/01/31 17:54:32 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CameraTransform.h"

void	CameraTransformInit(t_CameraTransform *camTransform, t_Transform worldFromCamera)
{
	t_Transform	renderFromWorld;

	renderFromWorld = Inverse(worldFromRender);
	camTransform->worldFromRender = Translate(P3ToV3f(transToP3f(worldFromCamera)));
	camTransform->renderFromCamera = TransMult(renderFromWorld, worldFromCamera);
}
