/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:45:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/06 16:38:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int				ft_allocate_map(t_setup *setup)
{
	int			array;

	if (!(MAP->map = (t_pix**)malloc(sizeof(t_pix*) * M_HEIGHT + 1)))
		return(0);
	MAP->mid[1] = (M_WIDTH * M_HEIGHT) / M_WIDTH;
	MAP->mid[0] = M_HEIGHT / 2;
	array = -1;
	while (MAP->tmp_map[++array])
		if(!(MAP->map[array] = (t_pix*)malloc(sizeof(t_pix) * M_WIDTH))) // erase + 1, see if V
			return(0);
	//printf("MAP witdh %d MAP height %d\n", M_WIDTH, M_HEIGHT);
	MAP->map[M_HEIGHT] = NULL;
	return (1);
}

static void		ft_matrix_cam(t_setup *setup)
{
	t_vec3 *vec3 = NULL;

	vec3 = ft_new_vec3(-CAM->pos->x, -CAM->pos->y, -CAM->pos->z);
	ft_matrix_rot_x(CAM->tmp_mat[0], -CAM->rot->x);
	ft_matrix_rot_y(CAM->tmp_mat[1], -CAM->rot->y);
	ft_matrix_rot_z(CAM->tmp_mat[2], -CAM->rot->z);
	ft_matrix_mult(CAM->tmp_mat[3], CAM->tmp_mat[2], CAM->tmp_mat[1], 4); // 3 2 1
	ft_matrix_mult(CAM->tmp_mat[4], CAM->tmp_mat[3], CAM->tmp_mat[0], 4);// 4 3 0
	ft_matrix_translate(CAM->tmp_mat[5], vec3); // 5
	ft_matrix_add(CAM->to_cam, CAM->tmp_mat[4], CAM->tmp_mat[5], 4);
	free (vec3);
}

static void		ft_vec3_to_pix(t_setup *setup, t_vec3 *vec3, int xy[2])
{
	int			oldz;

	//printf("mid %d %d\n", MAP->mid[0], MAP->mid[1]);
	ft_populate_vec3(vec3, (double)((xy[1] - MAP->mid[1]) * STEP), (double)\
			((xy[0] - MAP->mid[0]) * STEP),\
			(double)(MAP->tmp_map[xy[0]][xy[1]]));
	oldz = (int)(vec3->z);
	//printf("3dpoint %f %f %f\n", vec3->x, vec3->y, vec3->z);
	if (vec3->z > MAP->depth)
		MAP->depth = vec3->z;
	vec3->z = (double)(vec3->z * STEP * CAM->scale);
	ft_matrix_on_point(CAM->to_cam, vec3); // bypass temporarly
	ft_populate_pix(&MAP->map[xy[0]][xy[1]], (int)((CAM->fov / vec3->z) * \
				vec3->x), (int)((CAM->fov / vec3->z) * vec3->y), oldz);
}

//void		ft_print_matrix(double **mat, int size)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	ft_putstr("mat :\n");
//	while (i < size)
//	{
//		j = 0;
//		while (j < size)
//		{
//			printf("%f ", mat[i][j]);
//			j++;
//		}
//		i++;
//		ft_putchar('\n');
//	}
//}

int				ft_update_map_and_cam(t_setup *setup)
{
	int			xy[2];
	t_vec3		*vec3 = NULL;

	MAP->depth = 0;
	ft_matrix_cam(setup);
	//ft_print_matrix(CAM->to_cam, 4);
	if (!(vec3 = (t_vec3 *)(ft_memalloc(sizeof(t_vec3)))))
		return (0);
	xy[0] = -1;
	while (++xy[0] < M_HEIGHT)
	{
		xy[1] = -1;
		while (++xy[1] < M_WIDTH)
			ft_vec3_to_pix(setup, vec3, xy);
	}
	//ft_putchar('\n');
	free(vec3);
	return (1);
}
