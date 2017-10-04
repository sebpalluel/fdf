/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/08/30 17:45:14 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int					ft_free_tmp(char **tab, int fd, int return_val)
{
	if (tab && tab[0])
		ft_tabfree((void **)tab);
	if (fd)
		close(fd);
	return (return_val);
}

static int			ft_parse_map(t_setup *setup, char **tab)
{
	int			line;
	static int	error_line = 1;
	char		**split_ret = NULL;

	line = 0;
	while (line < M_HEIGHT)
	{
		if (!(split_ret = ft_strsplit((char const*)tab[line], ' ')))
			return (ft_free_tmp(split_ret, 0, 0));
		if ((error_line = ft_parse_line(setup, split_ret, line)) <= 0)
			return (ft_free_tmp(split_ret, 0, error_line));
		ft_tabfree((void **)split_ret);
		line++;
	}
	MAP->tmp_map[M_HEIGHT] = NULL;
	return (ft_free_tmp(NULL, 0, error_line));
}

int				ft_read_map(t_setup *setup, int fd)
{
	int			ret_gnl;
	char		**tab = NULL;

	M_HEIGHT = -1;
	tab = (char**)malloc(sizeof(char*) * MAX_SIZE);
	while ((ret_gnl = get_next_line(fd, &tab[++M_HEIGHT])))
		if (M_HEIGHT > MAX_SIZE)
			return (-2);
	tab[M_HEIGHT] = NULL;
	MAP->tmp_map = (int**)malloc(sizeof(int*) * M_HEIGHT + 1);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1  || !MAP->tmp_map || \
			!ft_parse_map(setup, tab))
		return (ft_free_tmp(tab, fd, -2));
	return (ft_free_tmp(tab, fd, 1)); 
}
