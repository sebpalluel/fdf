/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_map_depth.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:10:42 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 13:14:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		ft_depth_input(t_setup *setup, size_t w_flag)
{
	if (!MAPG->depth_t[w_flag])
	{
		if (ft_map_dim(setup, &MAPG->depth_i[w_flag], MAPG->depth_str[w_flag], \
					&MAPG->depth_t[w_flag]) == ERROR)
			return (ERROR);
		if (MAPG->depth_t[w_flag])
		{
			MAPG->depth[w_flag] = ft_atoi(MAPG->depth_str[w_flag]);
			if (MAPG->depth[w_flag] < MG_MIN_INT || MAPG->depth[w_flag] >\
					MG_MAX_INT)
				return (ERROR);
		}
	}
	return (OK);
}

int				ft_configure_depth(t_setup *setup)
{
	size_t		w_flag;
	static int	dim_col[2];

	w_flag = MAPG->dim_t[0];
	if (ft_depth_input(setup, w_flag) == ERROR)
		return (ERROR);
	dim_col[w_flag] = (MAPG->depth_t[w_flag] == 1) ? 65280 : 16711680;
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 50, \
			S_HEIGHT / 6, dim_col[0], "DEPTH MIN  : ");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 10, \
			S_HEIGHT / 6, dim_col[0], MAPG->depth_str[0]);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 50, \
			S_HEIGHT / 4, dim_col[1], "DEPTH MAX : ");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 10, \
			S_HEIGHT / 4, dim_col[1], MAPG->depth_str[1]);
	return (OK);
}

size_t		ft_name_input(t_setup *setup)
{
	char		*tmp;

	if (FD->name == NULL)
		if (!(FD->name = ft_strnew(1)))
			return (ERROR);
	if (SETUP.key != ENTER && MAPG->yes_t && ft_mlx_printkeytochar(SETUP.key))
	{
		if (!(tmp = ft_strdup(FD->name)))
			return (ERROR);
		free(FD->name);
		if (!(FD->name = ft_strnew(MAPG->name_i + 1)))
			return (ERROR);
		FD->name = tmp;
		FD->name[MAPG->name_i] = ft_mlx_printkeytochar(SETUP.key);
		FD->name[++MAPG->name_i] = '\0';
	}
	return (OK);
}
