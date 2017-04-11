/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:59:23 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 17:55:08 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void		ft_delete_map(t_setup *setup)
{
	if (MAP)
	{
		if (MAP->tmp_map && MAP->tmp_map[M_HEIGHT - 1])
			ft_tabfree((void **)MAP->tmp_map);
		if	(MAP->pix)
			free (MAP->pix);
		if	(MAP->map)
			ft_tabfree((void **)MAP->map);
		if (LERP_IN)
			free(LERP_IN);
		if (LERP_OUT)
			free(LERP_OUT);
		if (CLR)
			free(CLR);
		if (MAP->mid)
			free(MAP->mid);
		free(MAP);
	}
}

static void		ft_delete_cam(t_setup *setup)
{
	size_t		mat_inc;

	mat_inc = 0;
	if (CAM)
	{
		if (CAM->tmp_mat)
			while (CAM->tmp_mat[mat_inc++])
				ft_tabfree((void **)CAM->tmp_mat[mat_inc]);
		if (CAM->to_cam)
			ft_tabfree((void **)CAM->to_cam);
		if (CAM->pos)
			free(CAM->pos);
		if (CAM->rot)
			free(CAM->rot);
		free(CAM);
	}
}

static void		ft_delete_mlx(t_setup *setup)
{
	if (MLX)
	{
		if (IMG)
			ft_imgdel(IMG, MLX->mlx_ptr);
		if (MLX->mlx_ptr && MLX->win_ptr)
		{
			mlx_destroy_window(MLX->mlx_ptr, MLX->win_ptr);
			free(MLX->mlx_ptr);
		}
		free(MLX);
	}
}

t_setup			*ft_delete_setup(t_setup *setup)
{
	ft_delete_map(setup);
	ft_delete_cam(setup);
	ft_delete_mlx(setup);
	ft_memdel((void **)&(setup));
	return (NULL);
}
