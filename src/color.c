/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/20 16:24:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_color	*new_color(char r, char g, char b)
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
	color = new_color((unsigned char)ft_atoi(arg_color[0]), \
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
		setup->lerp_in = new_color(0, 0, 0);
		setup->lerp_out = new_color(255, 255, 255);
	}
	if (setup->lerp_in && setup->lerp_out)
		return (1);
	return (0);
}
