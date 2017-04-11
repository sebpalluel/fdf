/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 15:49:11 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void				ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr)
{
	unsigned int	index;
	int				mid_w;
	int				mid_h;

	mid_w = setup->width / 2;
	mid_h = setup->height / 2;
	index = (((mid_h + pix->y) * IMG->size_x) + ((mid_w + pix->x) * (IMG->bbp >> 3)));
	if ((pix->x < mid_w && pix->x > -mid_w) && (pix->y < mid_h && pix->y > -mid_h))
	{
		IMG->image_addr[index] = clr->b;
		IMG->image_addr[index + 1] = clr->g;
		IMG->image_addr[index + 2] = clr->r;
		IMG->image_addr[index + 3] = 0;
	}	
}

void				ft_draw_map_point(t_setup *setup)
{
	int				i;
	int				j;

	i = -1;
	while (++i < M_HEIGHT)
	{
		j = -1;
		while (++j < M_WIDTH)
		{
			ft_give_color(setup, CLR, MAP->map[i][j].z);
			ft_put_pix(setup, &MAP->map[i][j], CLR);
		}
	}
}
