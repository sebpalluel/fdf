/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 15:59:29 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		ft_allocate_matrix_cam(t_setup *setup)
{
	size_t		mat_inc;

	CAM->to_cam = ft_matrixzero(4);
	CAM->tmp_mat = (double ***)(ft_memalloc(sizeof(double **) * 7));
	if (!CAM->to_cam || !CAM->tmp_mat)
		return (0);
	mat_inc = 0;
	while (mat_inc < 6)
	{
		CAM->tmp_mat[mat_inc] = ft_matrixzero(4);
		if (!CAM->tmp_mat[mat_inc])
			return (0);
		mat_inc++;
	}
	CAM->tmp_mat[mat_inc] = NULL;
	return (1);
}

static int		ft_setup_cam(t_setup *setup, t_vec3 *pos, t_vec3 *rot, \
		double fov)
{
	if ((CAM = (t_cam*)ft_memalloc(sizeof(t_cam))) && setup && pos && rot)
	{
		CAM->pos = pos;
		CAM->rot = rot;
		CAM->scale = -1.;
		CAM->fov = fov;
		CAM->offset_x = (double)(setup->width / 2.0);
		CAM->offset_y = (double)(setup->height / 2.0);
		return (ft_allocate_matrix_cam(setup));
	}
	else
		return (0);
}

static int		ft_setup_map_and_mlx(t_setup *setup)
{
	t_map		*map = NULL;

	if ((map = (t_map*)ft_memalloc(sizeof(t_map))) && setup)
	{
		ft_memset(map, 0, sizeof(t_map));
		map->pix = (t_pix *)ft_memalloc(sizeof(t_pix));
		map->mid = (float *)ft_memalloc(sizeof(float) * 2);
		if (!map->mid || !map->pix)
			return (0);
		MAP = map;
	}
	MLX = ft_initwindow("fdf", setup->width, setup->height);
	IMG = ft_imgnew(MLX->mlx_ptr, setup->width, setup->height);
	if (MLX && MAP && IMG)
		return (1);
	return (0);
}

static t_setup	*ft_allocate_setup(int argc, char **argv)
{
	t_setup		*setup = NULL;

	if (!(setup = (t_setup *)ft_memalloc(sizeof(t_setup))))
		return (NULL);
	ft_memset(setup, 0, sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	SETUP.argc = argc;
	SETUP.argv = argv;
	FD = (t_fd *)ft_memalloc(sizeof(t_fd));
	ft_memset(FD, 0, sizeof(t_fd));
	if (ft_setup_cam(setup, ft_vec3new(0., 0., 1000.), \
				ft_vec3new(0., 0., 0.), 200.) \
			&& ft_setup_map_and_mlx(setup) && FD)
		return (setup);
	return (NULL);
}

t_setup			*ft_setup(int argc, char **argv, int *usage)
{
	t_setup 	*setup_tmp = NULL;

	setup_tmp = ft_allocate_setup(argc, argv);
	if ((*usage = ft_color_input(setup_tmp)) == -1)
		return (ft_delete_setup(setup_tmp));
	return (setup_tmp);
}
