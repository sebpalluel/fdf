/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/24 18:22:27 by psebasti         ###   ########.fr       */
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

int				main(int argc, char **argv)
{
	t_setup 	*setup = NULL;
	int			***tmp_map = NULL;
	int			ret;
	int			fd;

	if (argc < 2 || argc > 4)
		return (usage(0));
	ret = ft_setup(setup, argv, argc, 1);
	if (!ret || (fd = open(argv[1], O_RDONLY) < 3))
		return (usage(ret));
	if ((tmp_map = ft_read_map(setup, fd)))
		ft_mlx_process(setup, tmp_map);
	ft_setup(setup, argv, argc, 0);
	return (0);
}
