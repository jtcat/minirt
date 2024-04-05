/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:51:00 by joaoteix          #+#    #+#             */
/*   Updated: 2024/04/02 01:21:38 by jcat             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_filebuff
{
	char	data[BUFFER_SIZE];
	ssize_t	head;
	ssize_t	len;
}	t_filebuff;

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
ssize_t	parse_buff(char *buff, char *end, char **line, size_t *linelen);
char	*get_next_line(int fd);

#endif
