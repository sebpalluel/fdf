/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/08 17:37:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			*ft_allocate_map(t_setup *setup)
{
	int		*mid = NULL;
	int		array;

	if (!(mid = (int*)malloc(sizeof(int) * 2)))
		return(NULL);
	if (!((MAP)->map = (t_pix**)malloc(sizeof(t_pix*) * (MAP)->height + 1)))
		return(NULL);
	(MAP)->map[(MAP)->height] = NULL;
	mid[0] = MAP->width / 2;
	mid[1] = MAP->height / 2;
	array = -1;
	while ((MAP)->tmp_map[++array])
	{
		if(!((MAP)->map[array] = (t_pix*)malloc(sizeof(t_pix) * MAP->width + 1)))
			return(NULL);
	}
	return (mid);
}

static double	**ft_matrix_cam(t_cam *cam)
{
	double		**matrix_cam;
	t_vec3		*vec3;

	if (!(vec3 = ft_new_vec3(-cam->pos->x, -cam->pos->y, -cam->pos->z)))
		return (NULL);
	matrix_cam = ft_matrix_mult(ft_matrix_mult(
				ft_matrix_rot_z(-cam->rot->z),
				ft_matrix_rot_y(-cam->rot->y), 4),
			ft_matrix_rot_x(-cam->rot->x), 4);
	matrix_cam = ft_matrix_add(matrix_cam, ft_matrix_translate(vec3), 4);
	if (!matrix_cam || !*matrix_cam || !vec3)
	{
		ft_freetab((void **)matrix_cam);
		free(vec3);
		return (NULL);
	}
	matrix_cam[3][3] = 1;
	free(vec3);
	return (matrix_cam);
}

static t_pix	ft_vec3_to_pix(t_setup *setup, double **matrix,
		t_vec3 *vec3)
{
	t_pix		*pix;
	int			oldz;

	oldz = vec3->z;
	if (vec3->z > MAP->depth)
		MAP->depth = vec3->z;
	vec3->z = vec3->z * STEP * CAM->scale;
	ft_matrix_on_point(vec3, matrix);
	pix = ft_new_pix((CAM->fov / vec3->z) * vec3->x, (CAM->fov / vec3->z) \
			* vec3->y, oldz);
	return (*pix);
}

static int		ft_free_tmp_map(double **matrix, int *mid, t_vec3 *vec3,\
		int return_case)
{
	if (matrix)
	ft_freetab((void **)matrix);
	if (mid)
		free(mid);
	if (vec3)
		free(vec3);
	printf("update end\n");
	return (return_case);
}

int				ft_update_map_and_cam(t_setup *setup)
{
	int			xy[2];
	int			*mid = NULL;
	t_vec3		*vec3 = NULL;
	double		**matrix = NULL;

	MAP->depth = 0;
	if (!(matrix = ft_matrix_cam(CAM)) || !(mid = ft_allocate_map(setup)))
		return (ft_free_tmp_map(matrix, mid, vec3, 0));
	xy[0] = -1;
	printf("update map\n");
	while (MAP->tmp_map[++xy[0]])
	{
		xy[1] = -1;
		while (MAP->tmp_map[xy[0]][++xy[1]])
		{
			if (!(vec3 = ft_new_vec3((xy[0] - mid[0]) * STEP, (xy[1] - \
								mid[1]) * STEP, MAP->tmp_map[xy[0]][xy[1]])))
				return (ft_free_tmp_map(matrix, mid, vec3, 0));
			MAP->map[xy[0]][xy[1]] = ft_vec3_to_pix(setup, matrix, vec3);
		}
	}
	return (ft_free_tmp_map(matrix, mid, vec3, 1));
}
