/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/22 16:25:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_color	*ft_new_color(char r, char g, char b)
{
	t_color		*col;

	col = (t_color*)malloc(sizeof(t_color));
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

static int		ft_color_parse(char *arg, t_color *color)
{
	char		**arg_color;

	if (ft_strlen(arg) < 5 || ft_strlen(arg) > 11)
		return (0);
	arg_color = ft_strsplit(arg, ',');
	if (!arg_color || !arg_color[0] || !arg_color[1] || !arg_color[2])
		return (0);
	color = ft_new_color((unsigned char)ft_atoi(arg_color[0]), \
			(unsigned char)ft_atoi(arg_color[1]), \
			(unsigned char)ft_atoi(arg_color[2]));
	return (1);
}

int				ft_color_input(char **argv, int argc, t_setup *setup)
{
	if (argc == 4)
	{
		if (!ft_color_parse(argv[3], setup->lerp_in) || \
				!ft_color_parse(argv[4], setup->lerp_out))
			return (-1);
	}
	else
	{
		setup->lerp_in = ft_new_color(0, 0, 0);
		setup->lerp_out = ft_new_color(255, 255, 255);
	}
	if (setup->lerp_in && setup->lerp_out)
		return (1);
	return (0);
}

t_color				*give_color(int z, t_map *map)
{
	double		coef;
	double		rgb[3];

	if (z == 0)
		return (ft_new_color(map->clr_from->r,
					map->clr_from->g, map->clr_from->b));
	else if (z < 0)
		z = -z;
	else if (z == map->zmax)
		return (ft_new_color(map->clr_to->r, map->clr_to->g, map->clr_to->b));
	coef = (double)z / (double)(map->zmax);
	if (map->clr_to->r - map->clr_from->r)
		rgb[0] = (double)(map->clr_to->r - map->clr_from->r) * coef;
	else
		rgb[0] = map->clr_to->r;
	if (map->clr_to->g - map->clr_from->g)
		rgb[1] = (double)(map->clr_to->g - map->clr_from->g) * coef;
	else
		rgb[1] = map->clr_to->g;
	if (map->clr_to->b - map->clr_from->b)
		rgb[2] = (double)(map->clr_to->b - map->clr_from->b) * coef;
	else
		rgb[2] = map->clr_to->b;
	return (ft_new_color((char)rgb[0], (char)rgb[1], (char)rgb[2]));
}
