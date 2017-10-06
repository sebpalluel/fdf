/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:59:23 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 14:11:06 by psebasti         ###   ########.fr       */
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
			free(MAP->pix);
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

static void		ft_delete_map_gen(t_setup *setup)
{
	if (MAPG)
	{
		if	(MAPG->map_str)
			ft_tab3free((void ***)MAPG->map_str);
		free(MAPG);
	}
}

static void		ft_delete_cam(t_setup *setup)
{
	int			mat_inc;

	mat_inc = -1;
	if (CAM)
	{
		if (CAM->tmp_mat)
		{
			while (++mat_inc < 6)
			{
				if (CAM->tmp_mat[mat_inc])
					ft_tabfree((void **)CAM->tmp_mat[mat_inc]);
			}
			free (CAM->tmp_mat);
		}
		if (CAM->to_cam)
			ft_tabfree((void **)CAM->to_cam);
		if (CAM->pos)
			free(CAM->pos);
		if (CAM->rot)
			free(CAM->rot);
		free(CAM);
	}
}

t_setup			*ft_delete_setup(t_setup *setup)
{
	ft_delete_map(setup);
	ft_delete_map_gen(setup);
	ft_delete_cam(setup);
	if (FD)
		free(FD);
	ft_mlxdelete(MLX, IMG);
	free((void *)setup);
	return (NULL);
}
