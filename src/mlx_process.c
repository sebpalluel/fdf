/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/24 18:22:52 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int				ft_expose_hook(t_setup *setup)
{
	mlx_clear_window(MLX->mlx_ptr, MLX->win_ptr);
	ft_draw_map(setup);
	return (0);
}

void		ft_print_cam(t_setup *setup)
{
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 0, 16777215,
			" Position de la camera en x:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 0, 16777215,
			ft_itoa(CAM->pos->x));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 20, 16777215,
			"                      --  y:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 20, 16777215,
			ft_itoa(CAM->pos->y));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 40, 16777215,
			"                      --  z:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 40, 16777215,
			ft_itoa(CAM->pos->z));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 60, 16777215,
			"    Angle de la camera en x:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 60, 16777215,
			ft_itoa((int)(57.3 * CAM->rot->x)));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 80, 16777215,
			"                      --  y:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 80, 16777215,
			ft_itoa((int)(57.3 * CAM->rot->y)));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 100, 16777215,
			"                      --  z:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 289, 100, 16777215,
			ft_itoa((int)(57.3 * CAM->rot->z)));
}

static int				ft_key_hook(int keycode, t_setup *setup)
{

	if (CAM != 0)
	{
/*		if (keycode == 126)
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
			cam_zoom(CAM, -0.5);*/
	}
	if (keycode == 53)
	{
		ft_delete_setup(setup);
		exit(1);
	}
	ft_expose_hook(setup);
	return (0);
}

void		ft_mlx_process(t_setup *setup, int ***tmp_map)
{
	MLX->mlx_ptr = mlx_init();
	if (MLX->mlx_ptr != 0 && (MLX->win_ptr =
				mlx_new_window(MLX->mlx_ptr, setup->width,
					setup->height, "fdf")) != 0)
	{
		ft_print_cam(setup);
		ft_update_map_and_cam(setup, tmp_map);
		mlx_key_hook(MLX->win_ptr, ft_key_hook, setup);
		mlx_expose_hook(MLX->win_ptr, ft_expose_hook, setup);
		mlx_loop(MLX->mlx_ptr);
	}
}
