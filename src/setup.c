/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/29 16:16:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_pix			*ft_new_pix(int x, int y, int z)
{
	t_pix		*pix = NULL;

	if ((pix = (t_pix*)malloc(sizeof(t_pix))))
	{
		pix->x = x;
		pix->y = y;
		pix->z = z;
	}
	return (pix);
}

void			ft_populate_pix(t_pix *to_pix, int x, int y, int z)
{
	if (to_pix)
	{
		to_pix->x = x;
		to_pix->y = y;
		to_pix->z = z;
	}
}

static t_cam	*ft_allocate_matrix_cam(t_cam *cam)
{
	size_t		mat_inc;

	cam->to_cam = ft_matrix_zero(4);
	cam->tmp_mat = (double ***)(ft_memalloc(sizeof(double **) * 7));
	if (!cam->to_cam || !cam->tmp_mat)
		return (NULL);
	mat_inc = 0;
	while (mat_inc < 6)
	{
		cam->tmp_mat[mat_inc] = ft_matrix_zero(4);
		if (!cam->tmp_mat[mat_inc])
			return (NULL);
		mat_inc++;
	}
	cam->tmp_mat[mat_inc] = NULL;
	return (cam);
}

static int		ft_setup_cam(t_setup *setup, t_vec3 *pos, t_vec3 *rot, double fov)
{
	t_cam		*cam = NULL;

	if ((cam = (t_cam*)ft_memalloc(sizeof(t_cam))) && setup && pos && rot)
	{
		cam->pos = pos;
		cam->rot = rot;
		cam->scale = 1.;
		cam->fov = fov;
		cam->offset_x = (double)(setup->width / 2.0);
		cam->offset_y = (double)(setup->height / 2.0);
		CAM = ft_allocate_matrix_cam(cam);
	}
	if (CAM)
		return (1);
	return (0);
}

static int		ft_setup_map_and_mlx(t_setup *setup)
{
	t_map		*map = NULL;

	if ((map = (t_map*)ft_memalloc(sizeof(t_map))) && setup)
	{
		map->width = 0;
		map->height = 0;
		map->mid = (int *)ft_memalloc(sizeof(int) * 2);
		MAP = map;
	}
	MLX = ft_init_window("fdf", setup->width, setup->height);
	if (MLX && MAP)
		return (1);
	return (0);
}

static t_setup	*ft_allocate_setup()
{
	t_setup *setup = NULL;

	setup = (t_setup *)ft_memalloc(sizeof(t_setup));
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if (ft_setup_cam(setup, ft_new_vec3(WIDTH / STEP, HEIGHT / STEP, 1000.), \
				ft_new_vec3(0., 0., 0.), 2600.) \
			&& ft_setup_map_and_mlx(setup))
		return (setup);
	return (NULL);
}

t_setup			*ft_delete_setup(t_setup *setup)
{
	size_t mat_inc;

	mat_inc = 0;
		ft_memdel((void **)&(MAP->lerp_in));
		ft_memdel((void **)&(MAP->lerp_out));
		ft_memdel((void **)&(CAM->pos));
		ft_memdel((void **)&(CAM->rot));
		ft_freetab((void **)MAP->tmp_map);
		ft_memdel((void **)&(MAP->mid));
		//ADD ERASE FUNCTION FOR MAT
		ft_freetab((void **)CAM->to_cam);
		while (CAM->tmp_mat[mat_inc++])
			ft_freetab((void **)CAM->tmp_mat[mat_inc]);
		ft_memdel((void **)&(CAM));
		ft_memdel((void **)&(MAP));
		ft_memdel((void **)&(MLX));
		ft_memdel((void **)&(setup));
	return (NULL);
}

t_setup			*ft_setup(char **argv, int argc)
{
	t_setup 	*setup_tmp = NULL;

		setup_tmp = ft_allocate_setup();
		if (!ft_color_input(argv, argc, setup_tmp)\
				&& setup_tmp)
		return (ft_delete_setup(setup_tmp));
	return (setup_tmp);
}
