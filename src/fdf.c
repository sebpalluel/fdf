/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/01 14:57:20 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		usage(int mode)
{
	if (mode == 0)
	{
		ft_putendl("usage: ./fdf map_name.fdf");
		ft_putendl("usage: can add color arg1 lerp_in, arg5 lerp_out");
		ft_putendl("example: ./fdf map.fdf 0,0,0 255,255,255");
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
	int			fd;

	if (argc < 2 || argc > 4)
		return (usage(0));
	setup = ft_setup(setup, argv, argc, 1);
	fd = open(argv[1], O_RDONLY);
	if (!setup || (fd < 3))
		return (usage(0));
	if (ft_read_map(setup, fd))
		ft_mlx_process(setup);
	ft_setup(setup, argv, argc, 0);
	return (0);
}
