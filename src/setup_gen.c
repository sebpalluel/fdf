/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:25:41 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 17:47:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int				ft_setup_menu(t_setup *setup)
{
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 50, 0x00611DE9, MAPG_STR);
	if (!MAPG->dim_t[1])
	{
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 8, 0x009999FF, WIDTHG_STR);
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 5, 0x009999FF, HEIGHTG_STR);
		if (ft_configure_dim(setup) == ERROR)
			return (ERROR);
	}
	if (MAPG->dim_t[1] && !MAPG->depth_t[1])
	{
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 3.5, 0x009999FF, MINDEPTHG_STR);
		mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
				SETUP.height / 2.75, 0x009999FF, MAXDEPTHG_STR);
		if (ft_configure_depth(setup) == ERROR)
			return (ERROR);
	}
	if (MAPG->depth_t[1] && ft_generate_map(setup) == ERROR)
		return (ERROR);
	printf("setup_menu\n");
	return (OK);
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
