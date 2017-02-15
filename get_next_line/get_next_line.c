/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:46:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/01/29 17:43:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			copy_buff(t_fd *fd, char *src, t_char *buffer)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		if (buffer == NULL)
		{
			fd->buffer = (t_char *)ft_memalloc(sizeof(t_char));
			buffer = fd->buffer;
		}
		else
		{
			buffer->next = (t_char *)ft_memalloc(sizeof(t_char));
			buffer = buffer->next;
		}
		if (buffer == NULL)
			return (READ_ERR);
		buffer->c = src[i];
		buffer->next = NULL;
		i++;
	}
	return (READ_OK);
}

static int			read_buff(int fd, t_fd *fd_tab)
{
	t_char			*buffer;
	char			*src;
	int				ret;

	buffer = fd_tab[fd].buffer;
	while (buffer && buffer->next)
		buffer = buffer->next;
	if (!(src = ft_strnew(BUFF_SIZE)))
		return (READ_ERR);
	ret = read(fd, src, BUFF_SIZE);
	if (copy_buff(&fd_tab[fd], src, buffer) < 0)
		return (READ_ERR);
	free(src);
	return (ret);
}

static void			copy_line(size_t length, t_fd *fd, char **target)
{
	char 			*line;
	t_char			*current;
	t_char			*prev;

	line = ft_strnew(length);
	length = 0;
	current = fd->buffer;
	while (current->c != '\n')
	{
		line[length++] = current->c;
		prev = current;
		current = current->next;
		free(prev);
	}
	prev = current;
	current = current->next;
	free(prev);
	fd->buffer = current;
	*target = line;
}

static int			buffer_has_line(t_fd *fd, char **target)
{
	size_t			length;
	t_char			*current;

	current = fd->buffer;
	if (current == NULL)
		*target = NULL;
	length = 0;
	while (current != NULL && current->c != '\n')
	{
		current = current->next;
		length++;
	}
	if (current != NULL)
	{
		copy_line(length, fd, target);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd		fd_tab[FD_MAX];
	int				ret;

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (READ_ERR);
	if (buffer_has_line(&fd_tab[fd], line))
		return (READ_OK);
	ret = 1;
	while (!buffer_has_line(&fd_tab[fd], line) && ret > 0)
		ret = read_buff(fd, fd_tab);
	if (ret < 0)
		return (READ_ERR);
	if (ret > 0)
		return (READ_OK);
	return (READ_EOF);
}
