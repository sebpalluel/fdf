/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 17:47:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static double	**ft_matrix_cam(t_cam *cam)
{
	double		**to_cam_matrix;
	t_vec3		*vec3;

	vec3 = ft_new_vec3(-cam->pos->x, -cam->pos->y, -cam->pos->z);
	to_cam_matrix = mult_matrix(mult_matrix(
			give_rotation_matrix_z(-cam->rot->z),
			give_rotation_matrix_y(-cam->rot->y), 4),
			give_rotation_matrix_x(-cam->rot->x), 4);
	to_cam_matrix = add_matrix(to_cam_matrix, give_translation_matrix(vec3), 4);
	to_cam_matrix[3][3] = 1;
	return (to_cam_matrix);
}

int				ft_populate_map(t_setup *setup, int ***map_tmp)
{
	int			xy[2];
	int			*mid;
	t_vec3		*vec3;
	double		**final_matrix;

	final_matrix = ft_matrix_cam(CAM);
	MAP->map3D = map_tmp;
	MAP->depth = 0;
	mid = pre_map(&MAP);
	xy[0] = -1;
	while (map_tmp[++(xy[0])])
	{
		xy[1] = -1;
		while (map_tmp[(xy[0])][++(xy[1])])
		{
			vec3 = ft_new_vec3((xy[0] - mid[0]) * STEP, (xy[1] - mid[1]) * STEP,
								*map_tmp[xy[0]][xy[1]]);
			MAP->pix[xy[0]][xy[1]] = point_to_pix(final_matrix,
					vec3, CAM, MAP);
		}
	}
	return (1);
}
