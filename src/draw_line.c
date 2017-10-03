/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:42:31 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 19:27:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void			ft_line_to_pix(t_setup *setup, t_pix *a, double xyzi[4])
{
	ft_give_color(setup, CLR, MAP->pix->z);
	MAP->pix->x = a->x + round(xyzi[3] * xyzi[0]);
	MAP->pix->y = a->y + round(xyzi[3] * xyzi[1]);
	MAP->pix->z = a->z + round(xyzi[3] * xyzi[2]);
	ft_put_pix(setup, MAP->pix, CLR);
}

static void			ft_draw_line(t_setup *setup, t_pix *a, t_pix *b)
{
	double			xyzi[4];
	int				step;

	xyzi[3] = 0;
	ft_pixcpy(a, MAP->pix);
	if (abs(a->x - b->x) <= abs(a->y - b->y))
		step = 1 + abs(a->y - b->y);
	else
		step = 1 + abs(a->x - b->x);
	xyzi[0] = (double)(b->x - a->x) / step;
	xyzi[1] = (double)(b->y - a->y) / step;
	xyzi[2] = (double)(b->z - a->z) / step;
	if (step > MAX_STEP)
		step = MAX_STEP;
	while ((int)xyzi[3] < step)
	{
		ft_line_to_pix(setup, a, xyzi);
		xyzi[3]++;
	}
}


static void			ft_draw_map_column(t_setup *setup, int j)
{
	int				i;

	i = 0;
	while ((i + 1) < M_HEIGHT)
	{
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i + 1][j]);
		i++;
	}
}

static void			ft_draw_map_line(t_setup *setup, int i)
{
	int				j;

	j = 0;
	while ((j + 1) < M_WIDTH)
	{
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i][j + 1]);
		j++;
	}
}

void				ft_draw_map(t_setup *setup)
{
	int				xy[2];

	xy[0] = 0;
	while (xy[0] < M_HEIGHT)
	{
		ft_draw_map_line(setup, xy[0]);
		xy[0]++;
	}
	xy[1] = 0;
	while (xy[1] < M_WIDTH)
	{
		ft_draw_map_column(setup, xy[1]);
		xy[1]++;
	}
}
