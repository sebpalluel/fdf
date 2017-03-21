/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/21 16:32:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_color	*ft_new_color(unsigned char r, unsigned char g, \
		unsigned char b)
{
	t_color		*col = NULL;

	if ((col = (t_color*)malloc(sizeof(t_color))))
	{
		col->r = r;
		col->g = g;
		col->b = b;
	}
	return (col);
}

static int		ft_color_parse(char *arg, t_color *color)
{
	char		**arg_color = NULL;

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

t_color				*ft_give_color(int z, t_setup *setup)
{
	double		coef;
	double		rgb[3];

	if (z == 0)
		return (ft_new_color(LERP_IN->r,
					LERP_IN->g, LERP_IN->b));
	else if (z < 0)
		z = -z;
	else if (z == MAP->depth)
		return (ft_new_color(LERP_OUT->r, LERP_OUT->g, LERP_OUT->b));
	coef = (double)z / (double)(MAP->depth);
	if (LERP_OUT->r - LERP_IN->r)
		rgb[0] = (double)(LERP_OUT->r - LERP_IN->r) * coef;
	else
		rgb[0] = LERP_OUT->r;
	if (LERP_OUT->g - LERP_IN->g)
		rgb[1] = (double)(LERP_OUT->g - LERP_IN->g) * coef;
	else
		rgb[1] = LERP_OUT->g;
	if (LERP_OUT->b - LERP_IN->b)
		rgb[2] = (double)(LERP_OUT->b - LERP_IN->b) * coef;
	else
		rgb[2] = LERP_OUT->b;
	return (ft_new_color((char)rgb[0], (char)rgb[1], (char)rgb[2]));
}
