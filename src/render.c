/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:05:56 by joaoteix          #+#    #+#             */
/*   Updated: 2024/02/03 14:09:45 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	render(void)
{
	float	aspect_ratio = 16.0 / 9.0;
	int		image_width = 400;

	int		image_height = (image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;
}
