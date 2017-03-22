/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/22 01:35:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void			ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr)
{
	int		p;

	p = pix->x * 4 + pix->y * IMG->size_x;
	if (pix->y > 0 && pix->y < (int)setup->height && pix->x > 0 \
			&& pix->x < (int)setup->width)
	{
		IMG->image_addr[p] = clr->b;
		IMG->image_addr[p + 1] = clr->g;
		IMG->image_addr[p + 2] = clr->r;
	}
}

void				ft_clean_img(t_setup *setup)
{
	t_pix			p1;
	unsigned int	p;

	p1.y = 0;
	while (p1.y < (int)setup->height)
	{
		p1.x = 0;
		while (p1.x < (int)setup->width)
		{
			p = p1.x * 4 + p1.y * IMG->size_x;
			IMG->image_addr[p] = 0;
			IMG->image_addr[p + 1] = 0;
			IMG->image_addr[p + 2] = 0;
			p1.x++;
		}
		p1.y++;
	}
}

void			ft_draw_line(t_setup *setup, t_pix *a, t_pix *b)
{
	double		xyzi[3];
	int			i;
	int			step;
	t_pix		*pix = NULL;
	t_color		*clr = NULL;

	i = -1;
	//printf("a->x: %d, a->y: %d, a->z: %d\n", a->x, a->y, a->z);
	//printf("b->x: %d, b->y: %d, b->z: %d\n", b->x, b->y, b->z);
	if ((pix = ft_new_pix(a->x, a->y, a->z)))
	{
		//printf("pix->z: %d\n",pix->z);
		if (abs(a->x - b->x) <= abs(a->y - b->y))
			step = 1 + abs(a->y - b->y);
		else
			step = 1 + abs(a->x - b->x);
		xyzi[0] = (double)(b->x - a->x) / step;
		xyzi[1] = (double)(b->y - a->y) / step;
		xyzi[2] = (double)(b->z - a->z) / step;
		//printf("step: %d\n",step);
		while (++i < step)
		{
			if ((clr = ft_give_color(pix->z, setup)))
			{
				pix->x = a->x + round((double)(i * xyzi[0]));
				pix->y = a->y + round((double)(i * xyzi[1]));
				pix->z = a->z + round((double)(i * xyzi[2]));
				ft_put_pix(setup, pix, clr);
				free(clr);
			}
		}
		free(pix);
	}
	//	printf("end draw_line\n");
}

static void		ft_draw_map_column(t_setup *setup, int j)
{
	int	i;

	i = 0;
	while ((i + 1) < M_HEIGHT)
	{
		//	printf("draw_map_column x: %d, y: %d\n",j,i);
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i + 1][j]);
		//	printf("end draw_map_column\n");
		i++;
	}
}

static void		ft_draw_map_line(t_setup *setup, int i)
{
	int	j;

	j = 0;
	while ((j + 1) < M_WIDTH)
	{
		//	printf("draw_line x: %d, y: %d\n",j,i);
		ft_draw_line(setup, &MAP->map[i][j], &MAP->map[i][j + 1]);
		//	printf("end draw_map_line\n");
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
		while (&MAP->map[i][++j])
		{
			pix = &MAP->map[i][j];
			ft_put_pix(setup, pix, ft_give_color(pix->z, setup));
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
	printf("end_draw_map\n");
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
