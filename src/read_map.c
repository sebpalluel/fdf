/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/20 18:55:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			check_if_number(char **data, int *width)
{
	int		len;
	int		i;
	int		j;

	len = -1;
	while (data[++len])
		;
	*width = len;
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

static int			readed_to_map(t_setup *setup, int ***tab, char **readed)
{
	int			j;
	int			i;
	int			width;
	char		**split_ret;

	i = -1;
	width = MAP->width;
	MAP->height--;
	while (MAP->height - ++i + 1)
	{
		width = 0;
		split_ret = ft_strsplit((char const*)readed[i], ' ');
		if (!check_if_number(split_ret, &width))
			return (0);
		tab[MAP->height - i] = (int**)malloc(sizeof(int*) * width + 1);
		tab[MAP->height - i][width] = NULL;
		j = -1;
		while (++j < width)
		{
			(tab[MAP->height - i][width - j - 1]) = (int*)malloc(sizeof(int));
			*(tab[MAP->height - i][width - j - 1]) = ft_atoi(split_ret[j]);
		}
	}
	MAP->height++;
	ft_freetab(split_ret);
	return (1);
}

int					ft_read_map(t_setup *setup, int fd)
{
	int			***ret;
	int			ret_gnl;
	char		**tab = NULL;

	MAP->height = -1;
	tab = (char**)malloc(sizeof(char*) * MAX_SIZE);
	while ((ret_gnl = get_next_line(fd, &tab[MAP->height])))
		if (MAP->height > MAX_SIZE)
			return (0);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1)
		return (0);
	tab[MAP->height] = NULL;
	ret = (int***)malloc(sizeof(int**) * MAP->height + 1);
	ret[MAP->height] = NULL;
	if (!readed_to_map(setup, ret, tab))
		return (0);
	ft_freetab(tab);
	ft_freetab((char **)*ret);
	free(ret);
	close(fd);
	return (1);
}
