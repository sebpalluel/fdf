/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/22 18:24:29 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void			ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr)
{
	unsigned int	color;

	color = clr->r * 65536 + clr->g * 256 + clr->b;
	mlx_pixel_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 2 + pix->y,
			setup->height / 2 + pix->x, color);
}

void			ft_draw_line(t_setup *setup, t_pix *a, t_pix *b)
{
	double		xyzi[3];
	int			i;
	int			step;
	t_pix		*pix;
	t_color		*clr;

	i = -1;
	pix = ft_new_pix(a->x, a->y, a->z);
	if (abs(a->x - b->x) <= abs(a->y - b->y))
		step = 1 + abs(a->y - b->y);
	else
		step = 1 + abs(a->x - b->x);
	xyzi[0] = (double)(b->x - a->x) / step;
	xyzi[1] = (double)(b->y - a->y) / step;
	xyzi[2] = (double)(b->z - a->z) / step;
	while (++i < step)
	{
		clr = ft_give_color(pix->z, MAP);
		ft_put_pix(setup, pix, clr);
		pix->x = a->x + round((double)i * xyzi[0]);
		pix->y = a->y + round((double)i * xyzi[1]);
		pix->z = a->z + round((double)i * xyzi[2]);
		free(clr);
	}
	free(pix);
}

static void		ft_draw_map_column(t_setup *setup, int j)
{
	int	i;

	i = 0;
	while (MAP->map[i + 1])
	{
		ft_draw_line(setup, MAP->map[i][j], MAP->map[i + 1][j]);
		i++;
	}
}

static void		ft_draw_map_line(t_setup *setup, int i)
{
	int	j;

	j = 0;
	while (MAP->map[i][j + 1])
	{
		ft_draw_line(setup, MAP->map[i][j], MAP->map[i][j + 1]);
		j++;
	}
}

void			ft_draw_map_point(t_setup *setup)
{
	t_pix	*pix;
	int		i;
	int		j;

	pix = ft_new_pix(0, 0, 0);
	i = -1;
	while (MAP->map[++i])
	{
		j = -1;
		while (MAP->map[i][++j])
		{
			pix = MAP->map[i][j];
			ft_put_pix(setup, pix, ft_give_color(pix->z, MAP));
		}
	}
}

void			ft_draw_map(t_setup *setup)
{
	int i;

	i = 0;
	while (MAP->map[i])
	{
		ft_draw_map_line(setup, i);
		i++;
	}
	i = 0;
	while (MAP->map[0][i])
	{
		ft_draw_map_column(setup, i);
		i++;
	}
}
