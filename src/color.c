/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/03 18:40:11 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_color			*ft_new_color(unsigned char r, unsigned char g, \
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

static t_color	*ft_color_parse(char *arg)
{
	char		**arg_color = NULL;

	if (ft_strlen(arg) < 5 || ft_strlen(arg) > 11)
		return (NULL);
	arg_color = ft_strsplit(arg, ',');
	if (!arg_color || !arg_color[0] || !arg_color[1] || !arg_color[2])
		return (NULL);
	return (ft_new_color((unsigned char)ft_atoi(arg_color[0]), \
				(unsigned char)ft_atoi(arg_color[1]), \
				(unsigned char)ft_atoi(arg_color[2])));
}

void			ft_hexa_to_color(t_color *col, int hexValue)
{
	if (col)
	{
	col->r = (unsigned char)((hexValue >> 16) & 0xFF);
	col->g = (unsigned char)((hexValue >> 8) & 0xFF);
	col->b = (unsigned char)((hexValue) & 0xFF);
	}
}

t_color			*ft_hexcolor(int hexValue)
{
	t_color			*col = NULL;

	col = ft_new_color((unsigned char)((hexValue >> 16) & 0xFF),\
			(unsigned char)((hexValue >> 8) & 0xFF),\
			(unsigned char)((hexValue) & 0xFF));

	return (col);
}

int				ft_color_input(char **argv, int argc, t_setup *setup)
{
	if (argc == 4)
	{
		if (!(LERP_IN = ft_color_parse(argv[2])) || \
				!(LERP_OUT = ft_color_parse(argv[3])))
			return (-1);
	}
	if (argc == 2)
	{
		LERP_IN = ft_new_color(0, 0, 0);
		LERP_OUT = ft_new_color(255, 255, 255);
	}
	if (LERP_IN && LERP_OUT && (CLR = ft_new_color(0, 0, 0)))
		return (0);
	return (-1);
}

void				ft_clrcpy(t_color *clr_from, t_color *clr_to)
{
	if (clr_from && clr_to)
	{
		clr_to->r = clr_from->r;
		clr_to->g = clr_from->g;
		clr_to->b = clr_from->b;
	}
}

void				ft_give_color(t_setup *setup, t_color *clr, int z)
{
	double		coef;

	if (z == 0)
		return (ft_clrcpy(LERP_IN, clr));
	else if (z < 0)
		z = -z;
	else if (z == MAP->depth)
		return (ft_clrcpy(LERP_OUT, clr));
	coef = (double)z / (double)(MAP->depth);
	if (LERP_OUT->r - LERP_IN->r)
		clr->r = (double)(LERP_OUT->r - LERP_IN->r) * coef;
	else
		clr->r = LERP_OUT->r;
	if (LERP_OUT->g - LERP_IN->g)
		clr->g = (double)(LERP_OUT->g - LERP_IN->g) * coef;
	else
		clr->g = LERP_OUT->g;
	if (LERP_OUT->b - LERP_IN->b)
		clr->b = (double)(LERP_OUT->b - LERP_IN->b) * coef;
	else
		clr->b = LERP_OUT->b;
	return ;
}
