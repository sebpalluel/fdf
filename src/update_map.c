/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 16:29:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int				ft_allocate_map(t_setup *setup)
{
	int			array;

	if (!(MAP->map = (t_pix**)malloc(sizeof(t_pix*) * M_HEIGHT + 1)))
		return(ERROR);
	MAP->mid[1] = (M_WIDTH * M_HEIGHT) / M_WIDTH;
	MAP->mid[0] = M_HEIGHT / 2.;
	array = -1;
	while (MAP->tmp_map[++array])
		if(!(MAP->map[array] = (t_pix*)malloc(sizeof(t_pix) * M_WIDTH)))
			return(ERROR);
	MAP->map[M_HEIGHT] = NULL;
	return (OK);
}

static void		ft_matrix_cam(t_setup *setup)
{
	ft_matrixrotx(CAM->tmp_mat[0], -CAM->rot->x);
	ft_matrixroty(CAM->tmp_mat[1], -CAM->rot->y);
	ft_matrixrotz(CAM->tmp_mat[2], -CAM->rot->z);
	ft_matrixmult(CAM->tmp_mat[3], CAM->tmp_mat[2], CAM->tmp_mat[1], 4);
	ft_matrixmult(CAM->tmp_mat[4], CAM->tmp_mat[3], CAM->tmp_mat[0], 4);
	ft_matrixtranslate(CAM->tmp_mat[5], CAM->pos);
	ft_matrixadd(CAM->to_cam, CAM->tmp_mat[4], CAM->tmp_mat[5], 4);
}

static void		ft_vec3_to_pix(t_setup *setup, t_vec3 *vec3, int xy[2])
{
	int			oldz;

	ft_vec3populate(vec3, (double)((xy[1] - MAP->mid[1]) * STEP), (double)\
			((xy[0] - MAP->mid[0]) * STEP),\
			(double)(MAP->tmp_map[xy[0]][xy[1]]));
	oldz = (int)(vec3->z);
	if (vec3->z > MAP->depth)
		MAP->depth = vec3->z;
	vec3->z = (double)(vec3->z * STEP * CAM->scale);
	ft_matrixonpoint(CAM->to_cam, vec3);
	ft_pixpopulate(&MAP->map[xy[0]][xy[1]], (int)((CAM->fov / vec3->z) * \
				vec3->x), (int)((CAM->fov / vec3->z) * vec3->y), oldz);
}



int				ft_update_map_and_cam(t_setup *setup)
{
	int			xy[2];
	t_vec3		*vec3 = NULL;

	MAP->depth = 0;
	ft_matrix_cam(setup);
	if (!(vec3 = (t_vec3 *)(ft_memalloc(sizeof(t_vec3)))))
		return (ERROR);
	xy[0] = -1;
	while (++xy[0] < M_HEIGHT)
	{
		xy[1] = -1;
		while (++xy[1] < M_WIDTH)
			ft_vec3_to_pix(setup, vec3, xy);
	}
	free(vec3);
	return (OK);
}
