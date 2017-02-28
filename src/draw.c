/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/28 17:09:51 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void			ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr)
{
	int		p;

	p = pix->x * 4 + pix->y * MAP->width;
	if (pix->y > 0 && pix->y < setup->height && pix->x > 0 \
			&& pix->x < setup->width)
	{
		IMG->image_addr[p] = clr->b;
		IMG->image_addr[p + 1] = clr->g;
		IMG->image_addr[p + 2] = clr->r;
	}
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

void			ft_imgdel(t_img *img, void *mlx)
{
	if (img)
	{
		if (mlx && img->image)
			mlx_destroy_image(mlx, img->image);
		free(img);
	}
}

t_img				*ft_imgnew(void *mlx, size_t x, size_t y)
{
	int			bpp;
	t_img		*new;

	if (mlx)
	{
		if ((new = (t_img *)malloc(sizeof(t_img))))
		{
			if ((new->image = mlx_new_image(mlx, x, y)))
			{
				if ((new->image_addr = mlx_get_data_addr(new->image, &bpp,
						&new->size_x, (int *)&new->endian)))
				{
					new->bpp = bpp / 8;
					return (new);
				}
			}
		}
		ft_imgdel(new, mlx);
	}
	return (NULL);
}
