/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:49:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 18:40:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			ft_evaluate_length(t_setup *setup, char **tab)
{
	int				len;
	static int		width_state = 0;

	len = -1;
	while (tab[++len])
		;
	if (!width_state)
		width_state = len;
	if (width_state != len)
		return (0);
	M_WIDTH = len;
	return (1);
}

static void			ft_lerp_hexa(t_setup *setup, char **str, int line, int col)
{
	static int		max = 0;
	static int		min = MAX_INT;
	char			*hex;

	hex = str[1] + 2;
	MAP->tmp_map[line][col] = ft_atoi(str[0]);
	if (MAP->tmp_map[line][col] > max)
	{
		ft_hextocolor(MAP->lerp_in, (int)ft_strtol(hex, 16));
		max = MAP->tmp_map[line][col];
	}
	if (MAP->tmp_map[line][col] < min)
	{
		ft_hextocolor(MAP->lerp_out, (int)ft_strtol(hex, 16));
		min = MAP->tmp_map[line][col];
	}
	if (max == min)
	{
		MAP->lerp_in->r = 255;
		MAP->lerp_in->g = 255;
		MAP->lerp_in->b = 255;
	}
}

static int			ft_split_elem(t_setup *setup, char *str, int line, int col)
{
	char			**split_elem = NULL;

	if (str)
	{
		if (!MAP->hexa)
		{
			if (ft_checkint(str) != OK)
				return (0);
			MAP->tmp_map[line][col] = ft_atoi(str);
		}
		else
		{
			if (!(split_elem = ft_strsplit((char const *)str, ',')) && \
					ft_tabdepth((void **)split_elem) != 2)
				return (ft_free_tmp(split_elem, 0, 0));
			if (ft_checkint(split_elem[0]) != OK || \
					ft_checkhexa(split_elem[1]) != OK)
				return (ft_free_tmp(split_elem, 0, 0));
			ft_lerp_hexa(setup, split_elem, line, col);
			ft_tabfree((void **)split_elem);
		}
		return (1);
	}
	return (0);
}

static int			ft_have_hexa(t_setup *setup, char *str)
{
	size_t 			i;
	size_t			get_min;

	i = 0;
	MAP->hexa = 0;
	get_min = 0;
	while (str[i] != '\0')
	{
		if ((ft_isint(str[i]) != OK && ft_ishexa(str[i]) != OK &&\
					str[i] != 'x' && str[i] != ',') ||\
				((MAP->hexa && str[i] == ',') || (get_min && str[i] == '-')))
			return (0);
		if (str[i] == ',')
			MAP->hexa = 1;
		if (str[i] == '-')
			get_min = 1;
		i++;
	}
	return (1);
}

int					ft_parse_line(t_setup *setup, char **tab, int line)
{
	size_t			elem;

	if (!ft_evaluate_length(setup, tab))
	{
		MAP->tmp_map[line] = NULL;
		return (0);
	}
	if (!(MAP->tmp_map[line] = (int *)malloc(sizeof(int) * M_WIDTH)) )
	{
		return (-1);
	}
	elem = 0; 
	while (tab[elem] != '\0')
	{
		if (!ft_have_hexa(setup, tab[elem]))
			return (0);
		if (!ft_split_elem(setup, tab[elem], line, elem))
			return (0);
		elem++;
	}
	return (1);
}
