/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 15:26:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int				ft_expose_hook(t_setup *setup)
{
	int			x;
	int			y;

	mlx_clear_window(MLX->mlx_ptr, MLX->win_ptr);
	x = 0;
	while (x < M_WIDTH)
	{
		y = 0;
		while (y < M_HEIGHT)
		{
			if ((x + 1) < M_WIDTH)
				render_lines(setup, x, y, 1);
			if ((y + 1) < M_HEIGHT)
				render_lines(setup, x, y, 0);
			y++;
		}
		x++;
	}
	return (0);
}

static int				ft_key_hook(int keycode, t_setup *setup)
{

	if (CAM != 0)
	{
		if (keycode == 126)
			CAM->x += 1 / 50.0;
		if (keycode == 125)
			CAM->x -= 1 / 50.0;
		if (keycode == 123)
			CAM->y += 1 / 50.0;
		if (keycode == 124)
			CAM->y -= 1 / 50.0;
		if (keycode == 69)
			cam_zoom(CAM, 0.5);
		if (keycode == 78)
			cam_zoom(CAM, -0.5);
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
	MLX->mlx_ptr = mlx_init();
	if (MLX->mlx_ptr != 0 && (MLX->win_ptr =
				mlx_new_window(MLX->mlx_ptr, setup->width,
					setup->height, "fdf")) != 0)
	{
		cam_scale_to_obj(CAM, M_WIDTH, M_HEIGHT);
		mlx_key_hook(MLX->win_ptr, ft_key_hook, setup);
		mlx_expose_hook(MLX->win_ptr, ft_expose_hook, setup);
		mlx_loop(MLX->mlx_ptr);
	}
}
