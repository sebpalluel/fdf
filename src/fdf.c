/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 17:19:12 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		usage(int mode)
{
	if (mode == 0)
	{
		ft_putendl("usage: ./fdf map_name.fdf");
		ft_putendl("alternate usage: can add color arg1 lerp_in, arg2 lerp_out");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	if (mode == -1)
	{
		ft_putendl("error in alternate usage");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	return (-1);
}

static int		ft_populate_map(t_map *map, int ***map_tmp, t_cam *cam)
{
	int			ij[2];
	int			*mid;
	t_vec3		*point;
	double		**final_matrix;

	final_matrix = give_final_matrix(cam);
	map->map3D = map_tmp;
	map->zmax = 0;
	mid = pre_map(&map);
	ij[0] = -1;
	while (map_tmp[++(ij[0])])
	{
		ij[1] = -1;
		while (map_tmp[(ij[0])][++(ij[1])])
		{
			point = ft_new_vec3((ij[0] - mid[0]) * PAS, (ij[1] - mid[1]) * PAS,
								*map_tmp[ij[0]][ij[1]]);
			map->map[ij[0]][ij[1]] = point_to_pix(final_matrix,
					point, cam, map);
		}
	}
	return (1);
}

int				main(int argc, char **argv)
{
	t_setup 	*setup;
	int			***map_tmp;
	int			ret;
	int			fd;

	if (argc < 2 || argc > 4)
		return (usage(0));
	ret = ft_setup(setup, argv, argc, 1);
	if (!ret || (fd = open(argv[1], O_RDONLY) < 3))
		return (usage(ret));
	if ((map_tmp = ft_read_map(setup, fd)) &&\
			(ft_populate_map(MAP, map_tmp, CAM)))
		ft_mlx_process(setup);
	ft_setup(setup, argv, argc, 0);
	return (0);
}
