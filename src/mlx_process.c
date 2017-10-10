/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/10 15:20:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	ft_expose_hook(t_setup *setup)
{
	ft_imgclean(IMG, setup->width, setup->height);
	if (SETUP.mode == STATE_DRAW)
	{
		if (setup->line)
			ft_draw_map(setup);
		else
			ft_draw_map_point(setup);
		mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, 0, 0);
		if (setup->ui == 1)
			ft_print_cam(setup);
	}
	mlx_do_sync(MLX->mlx_ptr);
	return (0);
}

static int	ft_draw_update(t_setup *setup)
{
	ft_scale_cam(setup);
	ft_rot_cam(setup);
	ft_orient_cam(setup);
	if (SETUP.key == G_KEY)
		setup->ui = !setup->ui ? 1 : 0;
	if (SETUP.key == L_KEY)
		setup->line = !setup->line ? 1 : 0;
	return (ft_update_map_and_cam(setup));
}

int			ft_open_or_gen(t_setup *setup)
{
	if (ft_strcmp(SETUP.argv[1], "map_gen") == OK)
	{
		setup->mode = STATE_GEN;
		MAPG = (t_map_gen *)ft_memalloc(sizeof(t_map_gen));
		if (!MAPG)
			return (ERROR);
	}
	else
	{
		setup->mode = STATE_OPEN;
		if ((FD->fd = open(SETUP.argv[1], O_RDONLY)) <= 0)
		{
			SETUP.error = FILE_ERROR;
			return (ERROR);
		}
	}
	return (OK);
}

static int	ft_key_hook(int keycode, t_setup *setup)
{
	size_t	ret;

	SETUP.key = keycode;
	ret = OK;
	if (SETUP.mode == STATE_DRAW)
		ret = ft_draw_update(setup);
	ret = ft_setup_mode(setup, ret);
	if (SETUP.key == ESC || ret != OK)
	{
		ft_delete_setup(setup);
		usage(SETUP.error);
		exit(0);
	}
	ft_expose_hook(setup);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	if (SETUP.mode == STATE_START)
		ft_start(setup);
	mlx_key_hook(MLX->win_ptr, ft_key_hook, setup);
	mlx_expose_hook(MLX->win_ptr, ft_expose_hook, setup);
	mlx_do_sync(MLX->mlx_ptr);
	mlx_loop(MLX->mlx_ptr);
}
