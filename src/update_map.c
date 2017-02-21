/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 22:43:52 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			*ft_allocate_map(t_map **map)
{
	int		i;
	int		j;
	int		*ret;

	ret = (int*)malloc(sizeof(int) * 2);
	ret[1] = 0;
	i = -1;
	while ((*map)->tmp_map[++i])
		;
	(*map)->map = (t_pix***)malloc(sizeof(t_pix**) * i + 1);
	(*map)->map[i] = NULL;
	ret[0] = i / 2;
	i = -1;
	while ((*map)->tmp_map[++i])
	{
		j = -1;
		while ((*map)->tmp_map[i][++j])
			ret[1]++;
		(*map)->map[i] = (t_pix**)malloc(sizeof(t_pix*) * j + 1);
		(*map)->map[i][j] = NULL;
	}
	ret[1] = ret[1] / j;
	return (ret);
}

static double	**ft_matrix_cam(t_cam *cam)
{
	double		**to_cam_matrix;
	t_vec3		*vec3;

	vec3 = ft_new_vec3(-cam->pos->x, -cam->pos->y, -cam->pos->z);
	to_cam_matrix = ft_matrix_mult(ft_matrix_mult(
			ft_matrix_rot_z(-cam->rot->z),
			ft_matrix_rot_y(-cam->rot->y), 4),
			ft_matrix_rot_x(-cam->rot->x), 4);
	to_cam_matrix = ft_matrix_add(to_cam_matrix, ft_matrix_translate(vec3), 4);
	to_cam_matrix[3][3] = 1;
	return (to_cam_matrix);
}

int				ft_populate_map(t_setup *setup, int ***tmp_map)
{
	int			xy[2];
	int			*mid;
	t_vec3		*vec3;
	double		**final_matrix;

	final_matrix = ft_matrix_cam(CAM);
	MAP->tmp_map = tmp_map;
	MAP->depth = 0;
	mid = ft_allocate_map(&MAP);
	xy[0] = -1;
	while (tmp_map[++(xy[0])])
	{
		xy[1] = -1;
		while (tmp_map[(xy[0])][++(xy[1])])
		{
			vec3 = ft_new_vec3((xy[0] - mid[0]) * STEP, (xy[1] - mid[1]) * STEP,
								*tmp_map[xy[0]][xy[1]]);
			MAP->map[xy[0]][xy[1]] = point_to_pix(final_matrix,
					vec3, CAM, MAP);
		}
	}
	return (1);
}
