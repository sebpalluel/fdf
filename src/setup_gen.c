/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:25:41 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 19:22:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		ft_setup_dim(t_setup *setup)
{
	if (!MAPG->dim_t[1])
	{
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 8, 0x009999FF, WIDTHG_STR);
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 5, 0x009999FF, HEIGHTG_STR);
		if (ft_configure_dim(setup) == ERROR)
		{
			SETUP.error = DIM_ERROR;
			return (ERROR);
		}
	}
	return (OK);
}

static int		ft_setup_depth(t_setup *setup)
{
	if (MAPG->dim_t[1] && !MAPG->depth_t[1])
	{
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 3.5, 0x009999FF, MINDEPTHG_STR);
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 2.75, 0x009999FF, MAXDEPTHG_STR);
		if (ft_configure_depth(setup) == ERROR)
		{
			SETUP.error = DEPTH_ERROR;
			return (ERROR);
		}
	}
	return (OK);
}

int				ft_setup_menu(t_setup *setup)
{
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 50, 0x00611DE9, MAPG_STR);
	if (ft_setup_dim(setup) == ERROR)
		return (ERROR);
	if (ft_setup_depth(setup) == ERROR)
		return (ERROR);
	if (MAPG->depth_t[1] && ft_generate_map(setup) == ERROR)
		return (ERROR);
	return (OK);
}

int				ft_setup_mode(t_setup *setup, int ret)
{
	if (SETUP.key == ENTER && SETUP.mode == STATE_START)
	{
		ret = ft_open_or_gen(setup);
		mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, 0, 0);
	}
	if (ret == OK && SETUP.mode == STATE_GEN)
		ret = ft_setup_menu(setup);
	if (ret == OK && SETUP.mode == STATE_SAVE)
	{
		if ((ft_save_map(setup)) == OK)
			SETUP.mode = STATE_OPEN;
	}
	if (ret == OK && SETUP.mode == STATE_OPEN)
	{
		if (ft_read_map(setup) == OK && ft_allocate_map(setup) == OK\
				&& ft_update_map_and_cam(setup) == OK)
			SETUP.mode = STATE_DRAW;
		else
		{
			SETUP.error = MAP_ERROR;
			ret = ERROR;
		}
	}
	return (ret);
}

void			ft_start(t_setup *setup)
{
	size_t		xy[2];

	xy[0] = SETUP.width / 2 - SETUP.width / 14;
	xy[1] = SETUP.height / 2 - SETUP.height / 10;
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1], \
			0x00FFFFFF, START_STR);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1] + 30, \
			0x00FFFFFF, ENTER_STR);
}
