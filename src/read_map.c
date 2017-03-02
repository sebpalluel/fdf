/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/02 16:55:09 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void		ft_print_array_int(int **map, int width, int height)
{
	int		i;
	int		j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_putchar(' ');
			ft_putnbr(map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}

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
	char		**split_ret;

	i = 0;
	while (i < M_HEIGHT)
	{
		split_ret = ft_strsplit((char const*)tab[i], ' ');
		if (!ft_check_if_number(split_ret, &M_WIDTH) || !split_ret || \
				!(MAP->tmp_map[i] = \
					(int *)malloc(sizeof(int) * M_WIDTH + 1)))
			return (ft_free_tmp(split_ret, 0, 0));
		MAP->tmp_map[i][M_WIDTH] = 0;
		j = 0;
		while (j < M_WIDTH)
		{
			MAP->tmp_map[i][j] = ft_atoi(split_ret[j]);
			j++;
		}
		i++;
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
	{
		ft_putendl(tab[M_HEIGHT]);
		if (M_HEIGHT > MAX_SIZE)
			return (0);
	}
	tab[M_HEIGHT] = NULL;
	MAP->tmp_map = (int**)malloc(sizeof(int*) * M_HEIGHT + 1);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1  || !MAP->tmp_map || \
			!ft_parse_map(setup, tab))
		return (ft_free_tmp(tab, fd, 0));
	MAP->tmp_map[M_HEIGHT] = NULL;
	ft_print_array_int(MAP->tmp_map, M_WIDTH, M_HEIGHT);
	return (ft_free_tmp(tab, fd, 1)); 
}
