/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 12:40:19 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 18:29:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static size_t	ft_write_to_file(t_setup *setup)
{
	size_t		line;
	size_t		elem;
	size_t		numchar;
	size_t		mapdim[2];

	mapdim[0] = MG_HEIGHT;
	mapdim[1] = MG_WIDTH;
	line = 0;
	if (ft_open(FD, O_WRONLY, O_APPEND) != OK)
		return (ERROR);
	while (line < mapdim[0])
	{
		elem = 0;
		while (elem < mapdim[1])
		{
			numchar = ft_strlen(MAPG->map_str[line][elem]);
			if (write(FD->fd, MAPG->map_str[line][elem], numchar) < 0)
				return (ERROR);
			elem++;
		}
		line++;
	}
	return (OK);
}

static size_t	ft_save_file(t_setup *setup)
{
	int			name_col;

	name_col = (MAPG->name_t == 1) ? 65280 : 16711680;
	if (ft_name_input(setup) != OK)
		return (ERROR);
	if (setup->key == ENTER && *FD->name > 1)
	{
		if (!(FD->path = ft_strdup("maps/")))
			return (ERROR);
		ft_create_file(FD, 777);
		MAPG->name_t = 1;
	}
	name_col = (MAPG->name_t == 1) ? 65280 : 16711680;
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 2.7, 0x00611DE9, NAME_STR);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 2.5, name_col, FD->name);
	if (MAPG->name_t && ft_write_to_file(setup) == OK)
		return (OK);
	else
		return (ERROR);
}

int				ft_save_map(t_setup *setup)
{
	int			yn_col;
	size_t		ret;

	ret = ERROR;
	if (SETUP.key != Y_KEY && SETUP.key != N_KEY && !MAPG->yes_t)
		yn_col = 10066431;
	else
	{
		if (SETUP.key == Y_KEY || MAPG->yes_t)
		{
			ret = ft_save_file(setup);
			MAPG->yes_t = 1;
		}
		else if (SETUP.key == N_KEY)
			ret = OK;
		yn_col = (MAPG->yes_t == 1) ? 65280 : 16711680;
	}
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 3.3, 0x00611DE9, SAVE_STR);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, SETUP.width / 50, \
			SETUP.height / 3, yn_col, YESORNO_STR);
	return (ret);
}
