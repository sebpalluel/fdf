/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:46:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/05 21:07:09 by psebasti         ###   ########.fr       */
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
		map->pix = (t_pix *)ft_memalloc(sizeof(t_pix));
		map->mid = (int *)ft_memalloc(sizeof(int) * 2);
		if (!map->mid || !map->pix)
			return (0);
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

	if (!(setup = (t_setup *)ft_memalloc(sizeof(t_setup))))
		return (NULL);
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if (ft_setup_cam(setup, ft_new_vec3(0., 0., 1000.), \
				ft_new_vec3(0., 0., 0.), 2600.) \
			&& ft_setup_map_and_mlx(setup))
		return (setup);
	return (NULL);
}

static void		ft_delete_map(t_setup *setup)
{
	if (MAP)
	{
		if (MAP->tmp_map && MAP->tmp_map[M_HEIGHT - 1])
			ft_freetab((void **)MAP->tmp_map);
		if	(MAP->pix)
			free (MAP->pix);
		if	(MAP->map)
			ft_freetab((void **)MAP->map);
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

static void		ft_delete_cam(t_setup *setup)
{
	size_t mat_inc;

	mat_inc = 0;
	if (CAM)
	{
		if (CAM->tmp_mat)
			while (CAM->tmp_mat[mat_inc++])
				ft_freetab((void **)CAM->tmp_mat[mat_inc]);
		if (CAM->to_cam)
			ft_freetab((void **)CAM->to_cam);
		if (CAM->pos)
			free(CAM->pos);
		if (CAM->rot)
			free(CAM->rot);
		free(CAM);
	}
}

static	void	ft_delete_mlx(t_setup *setup)
{
	if (MLX)
	{
		if (IMG)
			ft_imgdel(IMG, MLX->mlx_ptr);
		if (MLX->mlx_ptr && MLX->win_ptr)
		{
			mlx_destroy_window(MLX->mlx_ptr, MLX->win_ptr);
			free(MLX->mlx_ptr);
		}
		free(MLX);
	}
}

t_setup			*ft_delete_setup(t_setup *setup)
{
	ft_delete_map(setup);
	ft_delete_cam(setup);
	ft_delete_mlx(setup);
	ft_memdel((void **)&(setup));
	return (NULL);
}

t_setup			*ft_setup(char **argv, int argc, int *usage)
{
	t_setup 	*setup_tmp = NULL;

	setup_tmp = ft_allocate_setup();
	if ((*usage = ft_color_input(argv, argc, setup_tmp)) == -1)
		return (ft_delete_setup(setup_tmp));
	return (setup_tmp);
}
