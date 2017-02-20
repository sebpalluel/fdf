/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/20 16:27:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int				ft_expose_hook(t_setup *setup)
{
	int			x;
	int			y;

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

static int				ft_key_hook(int keycode, t_setup *setup)
{

	if (setup->cam != 0)
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
		ft_delete_setup(setup);
		exit(1);
	}
	ft_expose_hook(setup);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	setup->mlx_ptr = mlx_init();
	if (setup->mlx_ptr != 0 && (setup->win_ptr =
				mlx_new_window(setup->mlx_ptr, setup->width,
					setup->height, "fdf")) != 0)
	{
		cam_scale_to_obj(setup->cam, setup->map->width, setup->map->height);
		mlx_key_hook(setup->win_ptr, ft_key_hook, setup);
		mlx_expose_hook(setup->win_ptr, ft_expose_hook, setup);
		mlx_loop(setup->mlx_ptr);
	}
}
