/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:39:27 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 19:15:30 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		usage2(int mode)
{
	if (mode == MAP_ERROR)
		ft_putendl(MAP_ERROR_S);
	else if (mode == DIM_ERROR)
		ft_putendl(DIM_ERROR_S);
	else if (mode == DEPTH_ERROR)
	{
		ft_putendl(DEPTH_ERROR_S);
		ft_putendl(DEPTH_ERROR2_S);
	}
	else if (mode == FILE_ERROR)
		ft_putendl(FILE_ERROR_S);
	return (mode);
}

int				usage(int mode)
{
	if (mode == OK)
		ft_putendl("program exited normally");
	else if (mode == ERROR)
	{
		ft_putendl("usage: ./fdf map_name.fdf");
		ft_putendl("usage: can add color arg1 lerp_in, arg5 lerp_out");
		ft_putendl("example: ./fdf map.fdf 0,0,0 255,255,255");
		ft_putendl("to generate a map, type:");
		ft_putendl("./fdf map_gen");
		ft_putendl("you can add colors too");
	}
	else if (mode == COLOR_ERROR)
	{
		ft_putendl("error in alternate usage");
		ft_putendl("example: ./fdf map.fdf \"0,0,0\" \"255,255,255\"");
	}
	return (usage2(mode));
}

int				main(int argc, char **argv)
{
	t_setup		*setup;
	static int	usage_ret = ERROR;

	if (argc < 2 || argc > 4)
		return (usage(usage_ret));
	setup = ft_setup(argc, argv, &usage_ret);
	if (!setup || usage_ret != OK)
		return (usage(usage_ret));
	SETUP.mode = STATE_START;
	ft_mlx_process(setup);
	return (0);
}
