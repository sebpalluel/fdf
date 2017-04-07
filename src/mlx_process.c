/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/07 15:26:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_mlx		*ft_init_window(char *name, int width, int height)
{
	t_mlx		*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, name);
	return (mlx);
}


static int				ft_expose_hook(t_setup *setup)
{
	if (!IMG)
		IMG = ft_imgnew(MLX->mlx_ptr, setup->width, setup->height);
	ft_clean_img(setup);
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
	if (keycode == ESC)
	{
		ft_delete_setup(setup);
		usage(1);
		//while (42);
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
	//printf("mlx_key_hook %d\n", keycode);
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
