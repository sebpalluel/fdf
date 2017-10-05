/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:22:36 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 14:45:02 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_color	*ft_color_parse(char *arg)
{
	char		**arg_color = NULL;

	if (ft_strlen(arg) < 5 || ft_strlen(arg) > 11)
		return (NULL);
	arg_color = ft_strsplit(arg, ',');
	if (!arg_color || !arg_color[0] || !arg_color[1] || !arg_color[2])
		return (NULL);
	return (ft_colornew((unsigned char)ft_atoi(arg_color[0]), \
				(unsigned char)ft_atoi(arg_color[1]), \
				(unsigned char)ft_atoi(arg_color[2])));
}

int				ft_color_input(t_setup *setup)
{
	if (SETUP.argc == 4)
	{
		if (!(LERP_IN = ft_color_parse(SETUP.argv[2])) || \
				!(LERP_OUT = ft_color_parse(SETUP.argv[3])))
			return (-1);
	}
	if (SETUP.argc == 2)
	{
		LERP_IN = ft_colornew(0, 0, 0);
		LERP_OUT = ft_colornew(255, 255, 255);
	}
	if (LERP_IN && LERP_OUT && (CLR = ft_colornew(0, 0, 0)))
		return (0);
	return (-1);
}

void				ft_give_color(t_setup *setup, t_color *clr, int z)
{
	double		coef;

	if (z == 0)
		return (ft_colorcpy(LERP_IN, clr));
	else if (z < 0)
		z = -z;
	else if (z == MAP->depth)
		return (ft_colorcpy(LERP_OUT, clr));
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
