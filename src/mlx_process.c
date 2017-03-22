/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/22 01:35:55 by psebasti         ###   ########.fr       */
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
	if (IMG == NULL)
		IMG = ft_imgnew(MLX->mlx_ptr, setup->width, setup->height);
	printf("bbp %d, endian %d, size_x %d\n", IMG->bbp, IMG->endian, IMG->size_x);
	//mlx_clear_window(MLX->mlx_ptr, MLX->win_ptr);
	ft_clean_img(setup); //clean image
	ft_draw_map(setup);
	printf("put_image\n");
	mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, M_WIDTH/2, M_HEIGHT/2);
	if (setup->ui == 1)
		ft_print_cam(setup);
	printf("mlx_do_sync\n");
	mlx_do_sync(MLX->mlx_ptr);
	return (0);
}

static int				ft_key_hook(int keycode, t_setup *setup)
{
	if (keycode == ESC)
	{
		ft_delete_setup(setup);
		exit (0);
		return (1);
	}
	if (CAM != 0)
	{
		ft_move_cam(setup, keycode);
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
	if (keycode == G_KEY)
	{
		setup->ui = !setup->ui ? 1 : 0;
		ft_expose_hook(setup);
	}
	ft_update_map_and_cam(setup);
	printf("mlx_key_hook %d\n", keycode);
	return (0);
}

void		ft_mlx_process(t_setup *setup)
{
	int		escape;

	escape = 0;
	while (!escape)
	{
		ft_update_map_and_cam(setup);
		escape = mlx_key_hook(MLX->win_ptr, ft_key_hook, setup);
		mlx_expose_hook(MLX->win_ptr, ft_expose_hook, setup);
		mlx_do_sync(MLX->mlx_ptr);
		printf("mlx_loop\n");
		mlx_loop(MLX->mlx_ptr);
	}
}
