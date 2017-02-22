/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/22 18:00:15 by psebasti         ###   ########.fr       */
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
		if (!ft_color_parse(argv[3], MAP->lerp_in) || \
				!ft_color_parse(argv[4], MAP->lerp_out))
			return (-1);
	}
	else
	{
		MAP->lerp_in = ft_new_color(0, 0, 0);
		MAP->lerp_out = ft_new_color(255, 255, 255);
	}
	if (MAP->lerp_in && MAP->lerp_out)
		return (1);
	return (0);
}

t_color				*give_color(int z, t_map *map)
{
	double		coef;
	double		rgb[3];

	if (z == 0)
		return (ft_new_color(map->lerp_in->r,
					map->lerp_in->g, map->lerp_in->b));
	else if (z < 0)
		z = -z;
	else if (z == map->depth)
		return (ft_new_color(map->lerp_out->r, map->lerp_out->g, map->lerp_out->b));
	coef = (double)z / (double)(map->depth);
	if (map->lerp_out->r - map->lerp_in->r)
		rgb[0] = (double)(map->lerp_out->r - map->lerp_in->r) * coef;
	else
		rgb[0] = map->lerp_out->r;
	if (map->lerp_out->g - map->lerp_in->g)
		rgb[1] = (double)(map->lerp_out->g - map->lerp_in->g) * coef;
	else
		rgb[1] = map->lerp_out->g;
	if (map->lerp_out->b - map->lerp_in->b)
		rgb[2] = (double)(map->lerp_out->b - map->lerp_in->b) * coef;
	else
		rgb[2] = map->lerp_out->b;
	return (ft_new_color((char)rgb[0], (char)rgb[1], (char)rgb[2]));
}
