/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/09 16:54:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_pix			*ft_new_pix(int x, int y, int z)
{
	t_pix		*pix;

	if ((pix = (t_pix*)malloc(sizeof(t_pix))))
	{
		pix->x = x;
		pix->y = y;
		pix->z = z;
	}
	return (pix);
}

static int		ft_setup_cam(t_setup *setup, t_vec3 *pos, t_vec3 *rot, double fov)
{
	t_cam		*cam = NULL;

	if ((cam = (t_cam*)ft_memalloc(sizeof(t_cam))) && setup && pos && rot)
	{
		cam->pos = pos;
		cam->rot = rot;
		cam->scale = 1.;
		cam->fov = fov;
		cam->offset_x = (double)(setup->width / 2.0);
		cam->offset_y = (double)(setup->height / 2.0);
		CAM = cam;
		return (1);
	}
	return (0);
}

static int		ft_setup_map_and_mlx(t_setup *setup)
{
	t_map		*map = NULL;

	if ((map = (t_map*)ft_memalloc(sizeof(t_map))) && setup)
	{
		map->width = 0;
		map->height = 0;
		MAP = map;
	}
	MLX = ft_init_window("fdf", setup->width, setup->height);
	if (MLX && MAP)
		return (1);
	return (0);
}

static t_setup	*ft_allocate_setup()
{
	t_setup *setup = NULL;

	setup = (t_setup *)ft_memalloc(sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if (ft_setup_cam(setup, ft_new_vec3(0., 0., 1500.),\
				ft_new_vec3(0., 0., 0.), 2000.) && ft_setup_map_and_mlx(setup))
		return (setup);
	return (NULL);
}

t_setup			*ft_delete_setup(t_setup *setup)
{
	ft_memdel((void **)&(MAP->lerp_in));
	ft_memdel((void **)&(MAP->lerp_out));
	ft_memdel((void **)&(CAM->pos));
	ft_memdel((void **)&(CAM->rot));
	ft_freetab((void **)MAP->tmp_map);
	ft_memdel((void **)&(CAM));
	ft_memdel((void **)&(MAP));
	ft_memdel((void **)&(MLX));
	ft_memdel((void **)&(setup));
	return (NULL);
}

t_setup			*ft_setup(t_setup *setup, char **argv, int argc, int allocate)
{
	t_setup 	*setup_tmp = NULL;

	setup_tmp = setup;
	if (allocate)
	{
		setup_tmp = ft_allocate_setup();
		allocate = ft_color_input(argv, argc, setup_tmp);
	}
	if ((!allocate && setup_tmp))
		return (ft_delete_setup(setup_tmp));
	return (setup_tmp);
}
