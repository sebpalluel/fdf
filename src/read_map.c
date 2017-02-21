/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 16:48:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void			ft_free_tmp(char **tab, int ***tab_int, int fd, int erase_tab)
{
	if (!erase_tab)
	{
		ft_freetab(tab);
		ft_freetab((char **)*tab_int);
	}
	free(tab_int);
	close(fd);
}

static int			ft_check_if_number(char **tab, int *width)
{
	int		len;
	int		i;
	int		j;

	len = -1;
	while (tab[++len])
		;
	*width = len;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (!ft_isdigit(tab[i][j]) &&\
						tab[i][j] != '-' && tab[i][j] != ' ')
				return (0);
	}
	return (1);
}

static int			ft_parse_map(t_setup *setup, int ***tab_int, char **tab)
{
	int			j;
	int			i;
	int			width;
	char		**split_ret;

	i = -1;
	width = M_WIDTH;
	M_HEIGHT--;
	while (M_HEIGHT - ++i + 1)
	{
		width = 0;
		split_ret = ft_strsplit((char const*)tab[i], ' ');
		if (!ft_check_if_number(split_ret, &width))
			return (0);
		tab_int[M_HEIGHT - i] = (int**)malloc(sizeof(int*) * width + 1);
		tab_int[M_HEIGHT - i][width] = NULL;
		j = -1;
		while (++j < width)
		{
			(tab_int[M_HEIGHT - i][width - j - 1]) = (int*)malloc(sizeof(int));
			*(tab_int[M_HEIGHT - i][width - j - 1]) = ft_atoi(split_ret[j]);
		}
	}
	ft_freetab(split_ret);
	return (1);
}

int					***ft_read_map(t_setup *setup, int fd)
{
	int			***tab_int = NULL;
	int			ret_gnl;
	char		**tab = NULL;

	M_HEIGHT = -1;
	tab = (char**)malloc(sizeof(char*) * MAX_SIZE);
	while ((ret_gnl = get_next_line(fd, &tab[++M_HEIGHT])))
		if (M_HEIGHT > MAX_SIZE)
			return (0);
	tab[M_HEIGHT] = NULL;
	tab_int = (int***)malloc(sizeof(int**) * M_HEIGHT + 1);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1  || !tab_int || \
			!ft_parse_map(setup, tab_int, tab))
	{
		ft_free_tmp(tab, tab_int, fd, 0);
		return (NULL);
	}
	ft_free_tmp(tab, tab_int, fd, 1);
	return (tab_int);
}
