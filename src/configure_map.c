/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:34:35 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 12:53:02 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		ft_map_dim(t_setup *setup, size_t *c, char *str, size_t *flag)
{
	if (setup->key != ENTER && *c < MAX_INT_DECIMAL)
	{
		if (ft_mlx_keytonumchar(setup->key) != '\0')
		{
			str[*c] = ft_mlx_keytonumchar(setup->key);
			str[++c[0]] = '\0';
		}
	}
	if (setup->key == ENTER && *str >= 1)
		*flag = 1;
	return (OK);
}

static int		ft_dim_input(t_setup *setup, size_t w_flag)
{
	if (!MAPG->dim_t[w_flag])
	{
		if (ft_map_dim(setup, &MAPG->dim_i[w_flag], MAPG->dim[w_flag], \
					&MAPG->dim_t[w_flag]) == ERROR)
			return (ERROR);
		if (MAPG->dim_t[w_flag])
		{
			MAPG->mapsize[w_flag] = ft_atoi(MAPG->dim[w_flag]);
			if (MAPG->mapsize[w_flag] < MG_MIN_SIZE || MAPG->mapsize[w_flag] >\
					MG_MAX_SIZE)
				return (ERROR);
		}
	}
	return (OK);
}

int				ft_configure_dim(t_setup *setup)
{
	size_t		w_flag;
	static int	dim_col[2];

	w_flag = MAPG->dim_t[0];
	if (ft_dim_input(setup, w_flag) == ERROR)
		return (ERROR);
	dim_col[w_flag] = (MAPG->dim_t[w_flag] == 1) ? 65280 : 16711680;
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 50, \
			S_HEIGHT / 6, dim_col[0], "WIDTH  : ");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 10, \
			S_HEIGHT / 6, dim_col[0], MAPG->dim[0]);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 50, \
			S_HEIGHT / 4, dim_col[1], "HEIGHT : ");
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, S_WIDTH / 10, \
			S_HEIGHT / 4, dim_col[1], MAPG->dim[1]);
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
