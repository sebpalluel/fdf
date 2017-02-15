/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/15 18:52:40 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	{
		if (!ft_color_parse(argv[3], setup->lerp_in) || \
				!ft_color_parse(argv[4], setup->lerp_out))
			return (-1);
	}
	else
	{
		setup->lerp_in = new_color(0, 0, 0);
		setup->lerp_out = new_color(255, 255, 255);
	}
	if (setup->lerp_in && setup->lerp_out)
		return (1);
	return (0);
}

static t_cam	*setup_cam(int width, int height)
{
	t_cam	*cam;

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

static int		ft_setup(t_setup *setup, char **argv, int argc, int allocate)
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



static int		usage(int mode)
{
	if (mode == 0)
	{
		ft_putendl("usage: ./fdf map_name.fdf");
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

int				ft_key_hook(int keycode, void *param)
{
	t_setup		*setup;

	setup = ft_use_setup(0);
	if (setup->cam != 0 && param == &(*param))
	{
		if (keycode == 126)
			setup->cam->x += 1 / 50.0;
		if (keycode == 125)
			setup->cam->x -= 1 / 50.0;
		if (keycode == 123)
			setup->cam->y += 1 / 50.0;
		if (keycode == 124)
			setup->cam->y -= 1 / 50.0;
		if (keycode == 69)
			cam_zoom(setup->cam, 0.5);
		if (keycode == 78)
			cam_zoom(setup->cam, -0.5);
	}
	if (keycode == 53)
	{
		ft_use_setup(2);
		exit(1);
	}
	expose_hook(0);
	return (0);
}

int				expose_hook(void *param)
{
	t_setup		*setup;
	int			x;
	int			y;

	setup = ft_use_setup(0);
	param = 0;
	mlx_clear_window(setup->mlx_ptr, setup->win_ptr);
	x = 0;
	while (x < setup->map->width)
	{
		y = 0;
		while (y < setup->map->height)
		{
			if ((x + 1) < setup->map->width)
				render_lines(setup, x, y, 1);
			if ((y + 1) < setup->map->height)
				render_lines(setup, x, y, 0);
			y++;
		}
		x++;
	}
	return (0);
}

static void		ft_mlx_process(t_setup *setup)
{
	setup->mlx_ptr = mlx_init();
	if (setup->mlx_ptr != 0 && (setup->win_ptr =
				mlx_new_window(setup->mlx_ptr, setup->width,
					setup->height, "fdf")) != 0)
	{
		cam_scale_to_obj(setup->cam, setup->map->width, setup->map->height);
		mlx_key_hook(setup->win_ptr, ft_key_hook, 0);
		mlx_expose_hook(setup->win_ptr, ft_expose_hook, 0);
		mlx_loop(setup->mlx_ptr);
	}
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
		ft_mlx_process(setup);

	}

	return (0);
}
