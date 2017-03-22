/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 00:37:02 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/22 01:23:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void			ft_orient_cam(t_setup *setup, int keycode)
{
	if (keycode == UP)
		CAM->pos->y = CAM->pos->y + STEP;
	else if (keycode == DOWN)
		CAM->pos->y = CAM->pos->y - STEP;
	else if (keycode == PLUS)
		CAM->pos->z = (CAM->pos->z == -STEP) ? STEP :
			CAM->pos->z + STEP;
	else if (keycode == MINUS)
		CAM->pos->z = (CAM->pos->z == STEP) ? -STEP :
			CAM->pos->z - STEP;
	else if (keycode == 15)
		CAM->rot->x = CAM->rot->x + (double)STEP / 100;
	else if (keycode == 3)
		CAM->rot->x = CAM->rot->x - (double)STEP / 100;
	else if (keycode == 16)
		CAM->rot->y = CAM->rot->y + (double)STEP / 100;
	else if (keycode == 4)
		CAM->rot->y = CAM->rot->y - (double)STEP / 100;
	else if (keycode == 17)
		CAM->rot->z = CAM->rot->z + (double)STEP / 100;
	else if (keycode == 5)
		CAM->rot->z = CAM->rot->z - (double)STEP / 100;
}

void			ft_move_cam(t_setup *setup, int keycode)
{
	ft_orient_cam(setup, keycode);
//	move_cam_3(CAM, keycode, mlx);
	if (keycode == 12)
		CAM->pos->x = CAM->pos->x + STEP;
	else if (keycode == 0)
		CAM->pos->x = CAM->pos->x - STEP;
	else if (keycode == 32)
	{
		CAM->scale = CAM->scale + (double)STEP / 100;
		if (CAM->scale == 0)
			CAM->scale = (double)STEP / 100;
	}
	else if (keycode == 38)
	{
		CAM->scale = CAM->scale - (double)STEP / 100;
		if (CAM->scale == 0)
			CAM->scale = -(double)STEP / 100;
	}
	else if (keycode == 24)
		CAM->fov = CAM->fov + STEP * 10;
	else if (keycode == 27)
		CAM->fov = CAM->fov - STEP * 10;
//	else if (keycode == 49)
//		CAM->line = (CAM->line == 0) ? 1 : 0;
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
