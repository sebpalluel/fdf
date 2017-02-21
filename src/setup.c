/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 16:18:40 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_vec3			*new_vec3(double x, double y, double z)
{
	t_vec3		*vec3;

	if ((vec3 = (t_vec3*)malloc(sizeof(t_vec3))))
	{
		vec3->x = x;
		vec3->y = y;
		vec3->z = z;
	}
	return (vec3);
}

static void		ft_setup_cam(t_setup *setup, t_vec3 *pos, t_vec3 *rot, double fov)
{
	t_cam		*cam = NULL;

	if ((cam = (t_cam*)ft_memalloc(sizeof(t_cam))) && setup && pos && rot)
	{
		cam->pos = pos;
		cam->rot = rot;
		cam->scale = 1.;
		cam->fov = fov;
		cam->offset_x = setup->width / 2.0;
		cam->offset_y = setup->height / 2.0;
	}
	CAM = cam;
}

static int		ft_allocate_setup(t_setup *setup)
{
	setup = (t_setup *)ft_memalloc(sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	ft_setup_cam(setup, new_vec3(0, 0, 1500), new_vec3(0, 0, 0), 2000);
	if (CAM && (MAP = (t_map *)ft_memalloc(sizeof(t_map))) && \
			(MLX = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		return (1);
	return (0);
}

void			ft_delete_setup(t_setup *setup)
{
	ft_memdel((void **)&(setup->lerp_in));
	ft_memdel((void **)&(setup->lerp_out));
	ft_memdel((void **)&(CAM->pos));
	ft_memdel((void **)&(CAM->rot));
	ft_memdel((void **)&(CAM));
	ft_memdel((void **)&(MAP));
	ft_memdel((void **)&(MLX));
	ft_memdel((void **)&(setup));
}

int				ft_setup(t_setup *setup, char **argv, int argc, int allocate)
{
	if (allocate)
	{
		allocate = ft_allocate_setup(setup);
		M_WIDTH = 0;
		M_HEIGHT = 0;
		allocate = ft_color_input(argv, argc, setup);
	}
	if (!allocate && setup)
		ft_delete_setup(setup);
	return (allocate);
}
