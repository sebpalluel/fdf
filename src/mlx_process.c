/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:27:00 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/21 19:06:31 by psebasti         ###   ########.fr       */
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

void				ft_clean_img(t_setup *setup)
{
	t_pix			p1;
	unsigned int	p;

	p1.y = 0;
	while (p1.y < (int)setup->height)
	{
		p1.x = 0;
		while (p1.x < (int)setup->width)
		{
			p = p1.x * 4 + p1.y * M_WIDTH;
			IMG->image_addr[p] = 0;
			IMG->image_addr[p + 1] = 0;
			IMG->image_addr[p + 2] = 0;
			p1.x++;
		}
		p1.y++;
	}
}

static int				ft_expose_hook(t_setup *setup)
{
	if (IMG == NULL)
		IMG = ft_imgnew(MLX->mlx_ptr, setup->width, setup->height);
	//mlx_clear_window(MLX->mlx_ptr, MLX->win_ptr);
	ft_draw_map(setup);
	//	ft_draw_image(setup); // method without IMG
	printf("put_image\n");
	mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG, 0, 0);
	//if (setup->ui == 1)
	//{
	ft_print_cam(setup);
	//draw on screen info
	//	}
	printf("mlx_do_sync\n");
	mlx_do_sync(MLX->mlx_ptr);
	ft_clean_img(setup); //clean image
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
	else if (CAM != 0)
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
	else if (keycode == CTRL)
	{
		setup->ui = !setup->ui ? 1 : 0;
		ft_expose_hook(setup);
	}
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
