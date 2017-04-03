/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:33:54 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/03 16:21:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

//void		ft_print_array_int(int **map, int width, int height)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	while (i < height)
//	{
//		j = 0;
//		while (j < width)
//		{
//			ft_putchar(' ');
//			ft_putnbr(map[i][j]);
//			j++;
//		}
//		ft_putchar('\n');
//		i++;
//	}
//}
//void	ft_print_array(char **array)
//{
//	int	i;
//
//	i = 0;
//	while (array[i])
//	{
//		ft_putendl(array[i]);
//		i++;
//	}
//}

static int			ft_free_tmp(char **tab, int fd, int return_val)
{
	if (tab && tab[0])
		ft_freetab((void **)tab);
	if (fd)
		close(fd);
	return (return_val);
}

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

static int			ft_checkhexa(char *str)
{
	size_t 			i;
	size_t			hexa_count;
	size_t			prefix;

	i = 0;
	hexa_count = 0;
	prefix = 0;
	while (str[i])
	{
		if (i == 0 && str[0] == '0' && str[1] == 'x')
		{
			prefix = 1;
			i += 2;
		}
		if (prefix && ft_ishexa(str[i]) && hexa_count < 7)
			hexa_count++;
		else
			return (0);
		i++;
	}
	return (1);
}

static int			ft_checkdigit(char *str)
{
	size_t			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int			ft_check_tab_depth(char **tab)
{
	size_t			depth;

	depth = 0;
	if (tab && *tab)
	{
		while (tab[depth])
			depth++;
	}
	return (depth);
}

static int			ft_return_del_tab(void **tab, int return_val)
{
	ft_freetab(tab);
	return (return_val);
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
		ft_hexa_to_color(MAP->lerp_in, (int)ft_strtol(hex, 16));
		max = MAP->tmp_map[line][col];
		printf("lerp_in %uc %uc %uc\n", MAP->lerp_in->r, MAP->lerp_in->g, MAP->lerp_in->b);
	}
	if (MAP->tmp_map[line][col] < min)
	{
		ft_hexa_to_color(MAP->lerp_out, (int)ft_strtol(hex, 16));
		min = MAP->tmp_map[line][col];
		printf("lerp_out %uc %uc %uc\n", MAP->lerp_out->r, MAP->lerp_out->g, MAP->lerp_out->b);
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
			if (!ft_checkdigit(str))
				return (0);
			MAP->tmp_map[line][col] = ft_atoi(str);
		}
		else
		{
			if (!(split_elem = ft_strsplit((char const *)str, ',')) && \
					ft_check_tab_depth(split_elem) != 2)
				return (ft_return_del_tab((void **)split_elem, 0)); // map error
			if (!ft_checkdigit(split_elem[0]) || !ft_checkhexa(split_elem[1]))
				return (ft_return_del_tab((void **)split_elem, 0)); // map error
			ft_lerp_hexa(setup, split_elem, line, col);
			ft_freetab((void **)split_elem);
		}
		return (1);
	}
	return (0);
}

static int			ft_have_hexa(t_setup *setup, char *str)
{
	size_t 			i;

	i = 0;
	MAP->hexa = 0;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && !ft_ishexa(str[i]) && str[i] != 'x' \
					&& str[i] != ',') || (MAP->hexa && str[i] == ','))
			return (0);
		if (str[i] == ',')
			MAP->hexa = 1;
		i++;
	}
	return (1);
}

static int			ft_parse_line(t_setup *setup, char **tab, int line)
{
	size_t			elem;

	if (!ft_evaluate_length(setup, tab))
		return (0); // map error
	if(!(MAP->tmp_map[line] = (int *)malloc(sizeof(int) * M_WIDTH + 1)))
		return (-1);
	MAP->tmp_map[line][M_WIDTH] = 0;
	elem = 0; 
	while (tab[elem])
	{
		if (!ft_have_hexa(setup, tab[elem]))
			return (0); // map error
		if (!ft_split_elem(setup, tab[elem], line, elem))
			return (0); // map error
		elem++;
	}	
	return (1);
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
		ft_freetab((void **)split_ret);
		line++;
	}
	MAP->tmp_map[M_HEIGHT] = NULL;
	return (ft_free_tmp(NULL, 0, error_line));
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
			return (-2);
	}
	tab[M_HEIGHT] = NULL;
	MAP->tmp_map = (int**)malloc(sizeof(int*) * M_HEIGHT + 1);
	if ((!tab || !tab[0] || !tab[0][0]) || ret_gnl == -1  || !MAP->tmp_map || \
			!ft_parse_map(setup, tab))
		return (ft_free_tmp(tab, fd, -2));
	//ft_print_array_int(MAP->tmp_map, M_WIDTH, M_HEIGHT); // was for debug, to remove after
	return (ft_free_tmp(tab, fd, 1)); 
}
