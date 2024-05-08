/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:05:32 by joaoteix          #+#    #+#             */
/*   Updated: 2024/05/08 14:04:32 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		buff[BUFFER_SIZE];
	static ssize_t	buff_i = 0;
	static ssize_t	res = 0;
	size_t			linelen;

	line = NULL;
	linelen = 0;
	if (fd > -1 && (!is_prevfd(fd) || buff_i == res))
	{
		res = read(fd, buff, BUFFER_SIZE);
		buff_i = 0;
	}
	while (res > 0 && (!line || line[linelen - 1] != '\n'))
	{
		if (buff_i >= res)
		{
			res = read(fd, buff, BUFFER_SIZE);
			buff_i = 0;
		}
		buff_i += parse_buff(buff + buff_i, buff + res, &line, &linelen);
	}
	if (line)
		line[linelen - 1] = '\0';
	return (line);
}
