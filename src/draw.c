/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/03 19:14:55 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void				ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr)
{
	unsigned int	index;

	index = (pix->y * IMG->size_x) + (pix->x * (IMG->bbp >> 3));
	if (pix->x > 0 && pix->x < (int)setup->width && pix->y > 0 \
			&& pix->y < (int)setup->height)
	{
		IMG->image_addr[index] = clr->b;
		IMG->image_addr[index + 1] = clr->g;
		IMG->image_addr[index + 2] = clr->r;
		IMG->image_addr[index + 3] = 0;
	}	
}

void				ft_clean_img(t_setup *setup)
{
	t_pix			p1;
	unsigned int	index;

	p1.y = 0;
	while (p1.y < (int)setup->height)
	{
		p1.x = 0;
		while (p1.x < (int)setup->width)
		{
			index = (p1.y * IMG->size_x) + (p1.x * (IMG->bbp >> 3));
			IMG->image_addr[index] = 0;
			IMG->image_addr[index + 1] = 0;
			IMG->image_addr[index + 2] = 0;
			p1.x++;
		}
		p1.y++;
	}
}

void			ft_pixcpy(t_pix *pix_from, t_pix *pix_to)
{
	if (pix_from && pix_to)
	{
		pix_to->x = pix_from->x;
		pix_to->y = pix_from->y;
		pix_to->z = pix_from->z;
	}
}

void			ft_line_to_pix(t_setup *setup, t_pix *a, double xyzi[4])
{
	ft_give_color(setup, CLR, MAP->pix->z);
	MAP->pix->x = a->x + round(xyzi[3] * xyzi[0]);
	MAP->pix->y = a->y + round(xyzi[3] * xyzi[1]);
	MAP->pix->z = a->z + round(xyzi[3] * xyzi[2]);
	ft_put_pix(setup, MAP->pix, CLR);
}

void			ft_draw_line(t_setup *setup, t_pix *a, t_pix *b)
{
	double		xyzi[4];
	int			step;

	xyzi[3] = 0;
	ft_pixcpy(a, MAP->pix);
	if (abs(a->x - b->x) <= abs(a->y - b->y))
		step = 1 + abs(a->y - b->y);
	else
		step = 1 + abs(a->x - b->x);
	xyzi[0] = (double)(b->x - a->x) / step;
	xyzi[1] = (double)(b->y - a->y) / step;
	xyzi[2] = (double)(b->z - a->z) / step;
	while ((int)xyzi[3] < step)
	{
		ft_line_to_pix(setup, a, xyzi);
		xyzi[3]++;
	}
}

static void		ft_draw_map_column(t_setup *setup, int j)
{
	int	i;

	i = 0;
	while ((i + 1) < M_HEIGHT)
	{
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i + 1][j]);
		i++;
	}
}

static void		ft_draw_map_line(t_setup *setup, int i)
{
	int	j;

	j = 0;
	while ((j + 1) < M_WIDTH)
	{
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i][j + 1]);
		j++;
	}
}

void			ft_draw_map_point(t_setup *setup)
{
	int		i;
	int		j;

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

void			ft_draw_map(t_setup *setup)
{
	int xy[2];

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
	t_img		*new;

	if (mlx)
	{
		if ((new = (t_img *)malloc(sizeof(t_img))))
		{
			if ((new->image = mlx_new_image(mlx, x, y)))
			{
				if ((new->image_addr = mlx_get_data_addr(new->image, &(new->bbp),
								&(new->size_x), &(new->endian))))
					return (new);
			}
		}
		ft_imgdel(new, mlx);
	}
	return (NULL);
}
