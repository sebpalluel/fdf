/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/07 21:13:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		ft_allocate_setup(t_setup *setup)
{
	setup = (t_setup *)ft_memalloc(sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if (setup->cam = setup_cam(setup->width, setup->height) && \
			setup->map = (t_map *)ft_memalloc(sizeof(t_map)))
		return (1);
	return (0);
}

static void		ft_delete_setup(t_setup *setup)
{
	ft_memdel((void **)&(setup->lerp_in));
	ft_memdel((void **)&(setup->lerp_out));
	ft_memdel((void **)&(setup->cam));
	ft_memdel((void **)&(setup->map->vector));
	ft_memdel((void **)&(setup->map));
	ft_memdel((void **)&(setup));
}

static t_setup	ft_setup(t_setup *setup, char **argv, int argc, int allocate)
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

static t_cam	*setup_cam(int width, int height)
{
	t_cam	*cam;

	if (cam = (t_cam*)ftmemalloc(sizeof(t_cam)))
	{
		cam->x = 0.5;
		cam->y = 0.5;
		cam->scale = 20;
		cam->offset_x = width / 2.0;
		cam->offset_y = height / 2.0;
	}
	return (cam);
}

static int		usage(int mode)
{
	if (mode == 0)
	{
		ft_putendl("usage: ./fdf mapname");
		ft_putendl("alternate usage: can add color arg1 lerp_in, arg2 lerp_out");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	if (mode == -1)
	{
		ft_putendl("error in alternate usage");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	return (-1);
}

t_color			*new_color(char r, char g, char b)
{
	t_color		*col;

	col = (t_color*)malloc(sizeof(t_color));
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

static int		ft_color_parse(char *arg, t_color *color)
{
	char		**arg_color;

	if (ft_strlen(arg) < 5 || ft_strlen(arg) > 11)
		return (0);
	arg_color = ft_strsplit(arg, ',');
	if (!arg_color || !arg_color[0] || !arg_color[1] || !arg_color[2])
		return (0);
	color = new_color((unsigned char)ft_atoi(arg_color[0]), \
			(unsigned char)ft_atoi(arg_color[1]), \
			(unsigned char)ft_atoi(arg_color[2]));
	return (1);
}

static int		ft_color_input(char **argv, int argc, t_setup *setup)
{
	if (argc == 4)
		if (!ft_color_parse(argv[3], setup->lerp_in) || \
				!ft_color_parse(argv[4], setup->lerp_out))
			return (-1);
		else
		{
			setup->lerp_in = new_color(0, 0, 0);
			setup->lerp_out = new_color(255, 255, 255);
		}
	if (setup->lerp_in && setup->lerp_out)
		return (1);
	return (0);
}

int				main(int argc, char **argv)
{
	t_setup 	*setup;
	int			ret;

	if (argc < 2 || argc > 4)
		return (usage(0));
	ret = ft_setup(setup, argv, argc, 1);
	if (!ret)
		return (usage(ret));
	else
	{
		

	}

	return (0);
}
