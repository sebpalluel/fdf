/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/20 16:47:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_cam	*setup_cam(int width, int height)
{
	t_cam		*cam;

	if ((cam = (t_cam*)ft_memalloc(sizeof(t_cam))))
	{
		cam->x = 0.5;
		cam->y = 0.5;
		cam->scale = 20;
		cam->offset_x = width / 2.0;
		cam->offset_y = height / 2.0;
	}
	return (cam);
}

static int		ft_allocate_setup(t_setup *setup)
{
	setup = (t_setup *)ft_memalloc(sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if ((setup->cam = setup_cam(setup->width, setup->height)) && \
			(setup->map = (t_map *)ft_memalloc(sizeof(t_map))))
		return (1);
	return (0);
}

static void		ft_delete_setup(t_setup *setup)
{
	ft_memdel((void **)&(setup->lerp_in));
	ft_memdel((void **)&(setup->lerp_out));
	ft_memdel((void **)&(setup->cam));
	ft_memdel((void **)&(setup->map->vec3));
	ft_memdel((void **)&(setup->map));
	ft_memdel((void **)&(setup));
}

int				ft_setup(t_setup *setup, char **argv, int argc, int allocate)
{

	if (allocate)
	{
		allocate = ft_allocate_setup(setup);
		setup->map->width = 0;
		setup->map->height = 0;
		allocate = ft_color_input(argv, argc, setup);
	}
	if (!allocate && setup)
		ft_delete_setup(setup);
	return (allocate);
}
