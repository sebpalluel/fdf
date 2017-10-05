/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 13:49:29 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int				usage(int mode)
{
	if (mode == 1)
		ft_putendl("program exited normally");
	else if (mode == 0)
	{
		ft_putendl("usage: ./fdf map_name.fdf");
		ft_putendl("usage: can add color arg1 lerp_in, arg5 lerp_out");
		ft_putendl("example: ./fdf map.fdf 0,0,0 255,255,255");
		ft_putendl("to generate a map type :");
		ft_putendl("./fdf gen_map");
		ft_putendl("you can add colors too");
	}
	else if (mode == -1)
	{
		ft_putendl("error in alternate usage");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	else if (mode == -2)
		ft_putendl("map error");
	return (mode);
}

int				main(int argc, char **argv)
{
	t_setup 	*setup;
	int			fd;
	static int	usage_ret = 0;

	if (argc < 2 || argc > 4)
		return (usage(usage_ret));
	setup = ft_setup(argv, argc, &usage_ret);
	setup->mode = STATE_START;
	if (ft_strcmp(argv[1], "gen_map") == OK)
		setup->mode = STATE_GEN;
	else
		fd = open(argv[1], O_RDONLY);
	if (!setup || (fd < 3) || (usage_ret = ft_read_map(setup, fd)) != 1)
		return (usage(usage_ret));
	if (ft_allocate_map(setup))
		ft_mlx_process(setup);
}
