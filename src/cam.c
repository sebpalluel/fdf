/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 00:37:02 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/27 19:40:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void			ft_scale_cam(t_setup *setup, int keycode)
{
	//	double			x_scale;
	//	double			y_scale;
	//
	//	else if (keycode == 32)
	//	{
	//		CAM->scale = CAM->scale + (double)STEP / 100;
	//		if (CAM->scale == 0)
	//			CAM->scale = (double)STEP / 100;
	//	}
	//	else if (keycode == 38)
	//	{
	//		CAM->scale = CAM->scale - (double)STEP / 100;
	//		if (CAM->scale == 0)
	//			CAM->scale = -(double)STEP / 100;
	//	}
	//
	//y_scale = setup->height / (CAM->offset_y * 1.4);
	//x_scale = setup->width / (CAM->offset_x * 1.4);
	//CAM->scale = x_scale;
	//if (y_scale > CAM->scale)
	//	CAM->scale = y_scale;
	//CAM->scale = 1 / CAM->scale;
	printf("test keycode %d\n", keycode);
	if (keycode == EQUAL)
	{
		CAM->scale = CAM->scale + (double)STEP / 100;
		printf("test scale %lf\n",CAM->scale);
//		if (CAM->scale == 0)
//			CAM->scale = (double)STEP / 100;
	}
	else if (keycode == MINUS)
	{
		CAM->scale = CAM->scale - (double)STEP / 100;
//		if (CAM->scale == 0)
//			CAM->scale = -(double)STEP / 100;
	}
}

static void			ft_orient_cam(t_setup *setup, int keycode)
{
	if (keycode == UP)
		CAM->pos->y = CAM->pos->y + STEP;
	else if (keycode == DOWN)
		CAM->pos->y = CAM->pos->y - STEP;
	else if (keycode == LEFT)
		CAM->pos->x = CAM->pos->x - STEP;
	else if (keycode == RIGHT)
		CAM->pos->x = CAM->pos->x + STEP;
	else if (keycode == DOT_KEY)
		CAM->pos->z = (CAM->pos->z == -STEP) ? STEP :
			CAM->pos->z + STEP;
	else if (keycode == SLASH_KEY)
		CAM->pos->z = (CAM->pos->z == STEP) ? -STEP :
			CAM->pos->z - STEP;
	else if (keycode == D_KEY)
		CAM->rot->x = CAM->rot->x + (double)STEP / 100;
	else if (keycode == A_KEY)
		CAM->rot->x = CAM->rot->x - (double)STEP / 100;
	else if (keycode == W_KEY)
		CAM->rot->y = CAM->rot->y + (double)STEP / 100;
	else if (keycode == S_KEY)
		CAM->rot->y = CAM->rot->y - (double)STEP / 100;
	else if (keycode == Q_KEY)
		CAM->rot->z = CAM->rot->z + (double)STEP / 100;
	else if (keycode == E_KEY)
		CAM->rot->z = CAM->rot->z - (double)STEP / 100;
	else if (keycode == R_KEY)
		CAM->fov = CAM->fov + STEP * 10;
	else if (keycode == F_KEY)
		CAM->fov = CAM->fov - STEP * 10;
}

void			ft_move_cam(t_setup *setup, int keycode)
{
	ft_scale_cam(setup, keycode);
	ft_orient_cam(setup, keycode);
	//	move_cam_3(CAM, keycode, mlx);
	//	else if (keycode == 49)
	//		CAM->line = (CAM->line == 0) ? 1 : 0;
}

void		ft_print_cam(t_setup *setup)
{
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 0, 16777215,
			" key LEFT/RIGHT    cam pos x:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 0, 16777215,
			ft_ftoa(CAM->pos->x));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 20, 16777215,
			" key UP/DOWN       cam pos y:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 20, 16777215,
			ft_ftoa(CAM->pos->y));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 40, 16777215,
			" key DOT/SLASH     cam pos z:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 40, 16777215,
			ft_ftoa(CAM->pos->z));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 60, 16777215,
			" key A/D           cam ang x:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 60, 16777215,
			ft_ftoa((int)(57.3 * CAM->rot->x)));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 80, 16777215,
			" key S/W           cam ang y:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 80, 16777215,
			ft_ftoa((int)(57.3 * CAM->rot->y)));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 100, 16777215,
			" key Q/E           cam ang z:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 100, 16777215,
			ft_ftoa((int)(57.3 * CAM->rot->z)));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 120, 16777215,
			" key F/R           cam fov:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 120, 16777215,
			ft_ftoa(CAM->fov));
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 140, 16777215,
			" key MINUS/EQUAL   cam scale:");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width/5, 140, 16777215,
			ft_ftoa(CAM->scale));
}
