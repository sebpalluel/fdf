/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/22 16:04:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		*ft_allocate_map(t_setup *setup)
{
	int		*mid = NULL;
	int		array;

	if (!(mid = (int*)malloc(sizeof(int) * 2)))
		return(NULL);
	if (!(MAP->map = (t_pix**)malloc(sizeof(t_pix*) * M_HEIGHT + 1)))
		return(NULL);
	mid[0] = M_WIDTH / 2;
	mid[1] = M_HEIGHT / 2;
	array = -1;
	while (MAP->tmp_map[++array])
	{
		if(!(MAP->map[array] = (t_pix*)malloc(sizeof(t_pix) * M_WIDTH))) // erase + 1, see if V
			return(NULL);
	}
	printf("MAP witdh %d MAP height %d\n", M_WIDTH, M_HEIGHT);
	MAP->map[M_HEIGHT] = NULL;
	return (mid);
}

static double	**ft_matrix_cam(t_setup *setup)
{
	t_vec3		*vec3;

	MAT->rot_x = ft_matrix_rot_x(-CAM->rot->x);
	MAT->rot_y = ft_matrix_rot_y(-CAM->rot->y);
	MAT->rot_z = ft_matrix_rot_z(-CAM->rot->z);
	MAT->mult_zy = ft_matrix_mult(MAT->rot_z, MAT->rot_y, 4);
	MAT->mult_rot = ft_matrix_mult(MAT->mult_zy, MAT->rot_x, 4);
	if (!(vec3 = ft_new_vec3(-CAM->pos->x, -CAM->pos->y, -CAM->pos->z)))
		return (NULL);
	MAT->trans = ft_matrix_translate(vec3);
	free(vec3);
	return (ft_matrix_add(MAT->mult_rot, MAT->trans, 4));
}

void			ft_free_matrix_cam(t_setup *setup)
{
	ft_freetab((void **)MAT->to_cam);
	ft_freetab((void **)MAT->mult_rot);
	ft_freetab((void **)MAT->mult_zy);
	ft_freetab((void **)MAT->rot_x);
	ft_freetab((void **)MAT->rot_y);
	ft_freetab((void **)MAT->rot_z);
	ft_freetab((void **)MAT->trans);
}

static t_pix	ft_vec3_to_pix(t_setup *setup, double **matrix,
		t_vec3 *vec3)
{
	t_pix		*pix = NULL;
	int			oldz;

	oldz = (int)(vec3->z);
	if (vec3->z > MAP->depth)
		MAP->depth = vec3->z;
	vec3->z = (double)(vec3->z * STEP * CAM->scale);
	ft_matrix_on_point(vec3, matrix); // bypass temporarly
	pix = ft_new_pix((int)((CAM->fov / vec3->z) * vec3->x), \
			(int)((CAM->fov / vec3->z) * vec3->y), oldz);
	return (*pix);
}

static int		ft_free_tmp_map(t_setup *setup, int *mid, t_vec3 *vec3,\
		int return_case)
{
	if (MAT->to_cam)
		ft_free_matrix_cam(setup);
	if (mid)
		free(mid);
	if (vec3 && !return_case)
		free(vec3);
	return (return_case);
}

int				ft_update_map_and_cam(t_setup *setup)
{
	int			xy[2];
	int			*mid = NULL;
	t_vec3		*vec3 = NULL;

	MAP->depth = 0;
	if (!(MAT->to_cam = ft_matrix_cam(setup)) || !(mid = ft_allocate_map(setup)))
		return (ft_free_tmp_map(setup, mid, vec3, 0));
	MAT->to_cam[3][3] = 1;
	xy[0] = 0;
	printf("mid[0]: %d mid[1] %d\n", mid[0], mid[1]);
	while (xy[0] < M_HEIGHT)
	{
		xy[1] = 0;
		while (xy[1] < M_WIDTH)
		{
			if (!(vec3 = ft_new_vec3((double)((xy[0] - mid[0]) * STEP), \
							(double)((xy[1] - mid[1]) * STEP), \
							(double)(MAP->tmp_map[xy[0]][xy[1]]))))
				return (ft_free_tmp_map(setup, mid, vec3, 0));
			MAP->map[xy[0]][xy[1]] = ft_vec3_to_pix(setup, MAT->to_cam, vec3);
			printf("l:%d w:%d,x:%d,y:%d,z:%d\n",xy[0], xy[1], MAP->map[xy[0]][xy[1]].x, MAP->map[xy[0]][xy[1]].y, MAP->map[xy[0]][xy[1]].z);
			xy[1]++;
		}
		//printf("newline %d\n",xy[0]);
		free(vec3);
		xy[0]++;
	}
	printf("update_map_and_cam\n");
	return (ft_free_tmp_map(setup, mid, vec3, 1));
}
