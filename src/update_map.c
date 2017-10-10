/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/10 14:59:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int				ft_allocate_map(t_setup *setup)
{
	int			array;

	if (!(MAP->map = (t_pix**)malloc(sizeof(t_pix*) * M_HEIGHT + 1)))
		return (ERROR);
	MAP->mid[0] = M_WIDTH / 2.;
	MAP->mid[1] = M_HEIGHT / 2.;
	array = -1;
	while (MAP->tmp_map[++array])
		if (!(MAP->map[array] = (t_pix*)malloc(sizeof(t_pix) * M_WIDTH)))
			return (ERROR);
	MAP->map[M_HEIGHT] = NULL;
	return (OK);
}

static void		ft_matrix_cam(t_setup *setup)
{
	ft_matrixrotx(CAM->M_ROT_X, -CAM->rot->x);
	ft_matrixroty(CAM->M_ROT_Y, -CAM->rot->y);
	ft_matrixrotz(CAM->M_ROT_Z, -CAM->rot->z);
	ft_matrixmult(CAM->M_ROT_ZY, CAM->M_ROT_Z, CAM->M_ROT_Y, 4);
	ft_matrixmult(CAM->M_ROT_ZYX, CAM->M_ROT_ZY, CAM->M_ROT_X, 4);
	ft_matrixtranslate(CAM->M_TRANS, CAM->pos);
	ft_matrixadd(CAM->to_cam, CAM->M_ROT_ZYX, CAM->M_TRANS, 4);
}

static void		ft_vec3_to_pix(t_setup *setup, t_vec3 *vec3, int xy[2])
{
	int			oldz;

	ft_vec3populate(vec3, (double)((xy[0] - MAP->mid[0]) * STEP), (double)\
			((xy[1] - MAP->mid[1]) * STEP),\
			(double)(MAP->tmp_map[xy[1]][xy[0]]));
	oldz = (int)(vec3->z);
	if (vec3->z > MAP->depth)
		MAP->depth = vec3->z;
	vec3->z = (double)(vec3->z * STEP * CAM->scale);
	ft_matrixonpoint(CAM->to_cam, vec3);
	ft_pixpopulate(&MAP->map[xy[1]][xy[0]], (int)((CAM->fov / vec3->z) * \
				vec3->x), (int)((CAM->fov / vec3->z) * vec3->y), oldz);
}

int				ft_update_map_and_cam(t_setup *setup)
{
	int			xy[2];
	t_vec3		*vec3;

	MAP->depth = 0;
	ft_matrix_cam(setup);
	if (!(vec3 = (t_vec3 *)(ft_memalloc(sizeof(t_vec3)))))
		return (ERROR);
	xy[1] = -1;
	while (++xy[1] < M_HEIGHT)
	{
		xy[0] = -1;
		while (++xy[0] < M_WIDTH)
			ft_vec3_to_pix(setup, vec3, xy);
	}
	free(vec3);
	return (OK);
}
