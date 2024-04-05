/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:25:57 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/04 00:17:38 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	readtobuff(int fd, t_filebuff *buff)
{
	buff->len = read(fd, buff->data, BUFFER_SIZE);
	buff->head = 0;
}

t_filebuff	*getbuff(int fd, t_filebuff **bufflist)
{
	if (fd == -1)
		return (NULL);
	if (!bufflist[fd])
	{
		bufflist[fd] = malloc(sizeof(t_filebuff));
		bufflist[fd]->len = 0;
		bufflist[fd]->head = 0;
	}
	return (bufflist[fd]);
}

void	clearbuff(int fd, t_filebuff **bufflist)
{
	free(bufflist[fd]);
	bufflist[fd] = NULL;
}

char	*get_next_line(int fd)
{
	static t_filebuff	*bufflist[10000] = {NULL};
	t_filebuff			*buff;
	char				*line;
	size_t				linelen;

	line = NULL;
	linelen = 0;
	buff = getbuff(fd, bufflist);
	if (!buff)
		return (NULL);
	if (buff->head == buff->len)
		readtobuff(fd, buff);
	while (buff->len > 0 && (!line || line[linelen - 1] != '\n'))
	{
		if (buff->head == buff->len)
			readtobuff(fd, buff);
		buff->head += parse_buff(buff->data + buff->head, buff->data \
		+ buff->len, &line, &linelen);
	}
	if (buff->len == 0)
		clearbuff(fd, bufflist);
	if (linelen > 0)
		line[linelen - 1] = '\0';
	return (line);
}
