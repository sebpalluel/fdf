/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/01 18:24:20 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	ft_expose_hook(t_setup *setup)
{
	if (!IMG)
		IMG = ft_imgnew(MLX->mlx_ptr, setup->width, setup->height);
	ft_imgclean(IMG, setup->width, setup->height);
	if (setup->line)
		ft_draw_map(setup);
	else
		ft_draw_map_point(setup);
	mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, 0, 0);
	if (setup->ui == 1)
		ft_print_cam(setup);
	mlx_do_sync(MLX->mlx_ptr);
	return (0);
}

static int	ft_key_hook(int keycode, t_setup *setup)
{
	if (keycode == ESC)
	{
		ft_delete_setup(setup);
		usage(1);
		while (42);
		exit (0);
	}
	ft_scale_cam(setup, keycode);
	ft_rot_cam(setup, keycode);
	ft_orient_cam(setup, keycode);
	if (keycode == G_KEY)
		setup->ui = !setup->ui ? 1 : 0;
	if (keycode == L_KEY)
		setup->line = !setup->line ? 1 : 0;
	ft_update_map_and_cam(setup);
	ft_expose_hook(setup);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	ft_update_map_and_cam(setup);
	mlx_key_hook(MLX->win_ptr, ft_key_hook, setup);
	mlx_expose_hook(MLX->win_ptr, ft_expose_hook, setup);
	mlx_do_sync(MLX->mlx_ptr);
	mlx_loop(MLX->mlx_ptr);
}
