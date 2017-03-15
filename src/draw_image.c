/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 20:24:22 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/07 15:10:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_color_in_image(t_setup *setup, int x, int y)
{
	t_color	col;
	int		p;

	u.color = setup->color;
	p = x * 4 + y * setup->size_line;
	if (y > 0 && y < WIN_Y && x > 0 && x < WIN_X)
	{
		IMG->image_addr[p] = u.rgb.b;
		IMG->image_addr[p + 1] = u.rgb.g;
		IMG->image_addr[p + 2] = u.rgb.r;
	}
}

void	create_image(t_setup *setup)
{
	IMG->endian = ENDIAN;
	IMG->bbp = BBP;
	IMG->image = mlx_new_image(setup->mlx, M_WIDTH, M_HEIGHT);
	IMG->image_addr = mlx_get_data_addr(IMG->image, &(IMG->bbp), &(MAP->width)\
			, &(IMG->endian));
}

void	ft_draw_line(t_pix p1, t_pix p2, t_setup *setup)
{
	t_pix		d;
	t_pix		s;
	int			err;
	int			e2;

	d.x = ABS(p2.x - p1.x);
	d.y = ABS(p2.y - p1.y);
	s.x = p1.x < p2.x ? 1 : -1;
	s.y = p1.y < p2.y ? 1 : -1;
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (42)
	{
		draw_color_in_image(setup, p1.x, p1.y);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = err;
		if (e2 > -d.x && ((err -= d.y) || !err))
			p1.x += s.x;
		if (e2 < d.y)
		{
			err += d.x;
			p1.y += s.y;
		}
	}
}

void	ft_draw_image(t_setup *setup)
{
	int		y;
	int		x;
	t_pix	p1;
	t_pix	p2;
	int		xx;

	y = -1;
	while (++y < setup->y - 1)
	{
		x = -1;
		xx = setup->pos_x - (y * setup->size / 2);
		while (++x < setup->x - 1)
		{
			get_color(y, x, setup);
			p1.y = setup->pos_y + (y * setup->size - (setup->map[y][x] * PIKE));
			p1.x = xx + x * setup->size;
			p2.y = setup->pos_y + ((y + 1) * setup->size - (setup->map[y + 1][x] * PIKE));
			p2.x = setup->pos_x - ((y + 1) * setup->size / 2) + x * setup->size;
			ft_draw_line(p1, p2, setup);
			p2.y = setup->pos_y + (y * setup->size - (setup->map[y][x + 1] * PIKE));
			p2.x = xx + (x + 1) * setup->size;
			ft_draw_line(p1, p2, setup);
		}
	}
	ft_draw_border(setup);
}
