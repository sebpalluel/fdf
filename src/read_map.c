/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/20 17:33:28 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			check_if_number(char **data, int *length)
{
	int		len;
	int		i;
	int		j;

	len = -1;
	while (data[++len])
		;
	*length = len;
	i = -1;
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
			if ((data[i][j] < 48 || data[i][j] > 57)
					&& data[i][j] != 45 && data[i][j] != ' ')
				return (0);
	}
	return (1);
}

static int			readed_to_map(int ***tab, char **readed, int size)
{
	int			j;
	int			i;
	int			length;
	char		**split_ret;

	i = -1;
	size--;
	while (size - ++i + 1)
	{
		length = 0;
		split_ret = ft_strsplit((char const*)readed[i], ' ');
		if (!check_if_number(split_ret, &length))
			return (0);
		tab[size - i] = (int**)malloc(sizeof(int*) * length + 1);
		tab[size - i][length] = NULL;
		j = -1;
		while (++j < length)
		{
			(tab[size - i][length - j - 1]) = (int*)malloc(sizeof(int));
			*(tab[size - i][length - j - 1]) = ft_atoi(split_ret[j]);
		}
	}
	ft_freetab(split_ret);
	return (1);
}

int					ft_read_map(t_setup *setup, int fd)
{
	int			***ret;
	int			ret_gnl;
	int			i;
	char		**tab = NULL;

	i = -1;
	while ((ret_gnl = get_next_line(fd, &tab[++i])))
	{

		i++;
	}
	ret = (int***)malloc(sizeof(int**) * i + 1);
	ret[i] = NULL;
	if (!readed_to_map(ret, tab, i))
		return (0);
	ft_freetab(tab);
	close(fd);
	return (1);
}
