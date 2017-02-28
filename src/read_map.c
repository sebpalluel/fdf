/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/28 17:13:02 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			ft_free_tmp(char **tab, int fd, int return_val)
{
	if (tab)
		ft_freetab(tab);
	if (fd)
	close(fd);
	return (return_val);
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

static int			ft_parse_map(t_setup *setup, char **tab)
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
		if (!ft_check_if_number(split_ret, &width) || !split_ret || \
				!(MAP->tmp_map[M_HEIGHT - i] = \
					(int*)malloc(sizeof(int) * M_WIDTH + 1)))
			return (ft_free_tmp(split_ret, 0, 0));
		MAP->tmp_map[M_HEIGHT - i][width] = 0;
		j = -1;
		while (++j < width)
			MAP->tmp_map[M_HEIGHT - i][width - j - 1] = ft_atoi(split_ret[j]);
	}
	return (ft_free_tmp(split_ret, 0, 1));
}

int					ft_read_map(t_setup *setup, int fd)
{
	int			ret_gnl;
	char		**tab = NULL;

	M_HEIGHT = -1;
	tab = (char**)malloc(sizeof(char*) * MAX_SIZE);
	while ((ret_gnl = get_next_line(fd, &tab[++M_HEIGHT])))
		if (M_HEIGHT > MAX_SIZE)
			return (0);
	tab[M_HEIGHT] = NULL;
	MAP->tmp_map = (int**)malloc(sizeof(int*) * M_HEIGHT + 1);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1  || !MAP->tmp_map || \
			!ft_parse_map(setup, tab))
		return (ft_free_tmp(tab, fd, 0));
	return (ft_free_tmp(tab, fd, 1));
}
