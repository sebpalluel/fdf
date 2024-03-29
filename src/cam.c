/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 00:37:02 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 19:38:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void		ft_scale_cam(t_setup *setup)
{
	if (SETUP.key == EQUAL)
		CAM->scale += (double)STEP / 100;
	else if (SETUP.key == MINUS)
		CAM->scale -= (double)STEP / 100;
}

void		ft_rot_cam(t_setup *setup)
{
	if (SETUP.key == D_KEY)
		CAM->rot->x = CAM->rot->x + (double)STEP / 100;
	else if (SETUP.key == A_KEY)
		CAM->rot->x = CAM->rot->x - (double)STEP / 100;
	else if (SETUP.key == W_KEY)
		CAM->rot->y = CAM->rot->y + (double)STEP / 100;
	else if (SETUP.key == S_KEY)
		CAM->rot->y = CAM->rot->y - (double)STEP / 100;
	else if (SETUP.key == Q_KEY)
		CAM->rot->z = CAM->rot->z + (double)STEP / 100;
	else if (SETUP.key == E_KEY)
		CAM->rot->z = CAM->rot->z - (double)STEP / 100;
}

void		ft_orient_cam(t_setup *setup)
{
	if (SETUP.key == UP)
		CAM->pos->y = CAM->pos->y + AMP * 10;
	else if (SETUP.key == DOWN)
		CAM->pos->y = CAM->pos->y - AMP * 10;
	else if (SETUP.key == LEFT)
		CAM->pos->x = CAM->pos->x - AMP * 10;
	else if (SETUP.key == RIGHT)
		CAM->pos->x = CAM->pos->x + AMP * 10;
	else if (SETUP.key == DOT_KEY)
		CAM->pos->z = (CAM->pos->z == -AMP) ? AMP :
			CAM->pos->z + AMP * 10;
	else if (SETUP.key == SLASH_KEY)
		CAM->pos->z = (CAM->pos->z == AMP) ? -AMP :
			CAM->pos->z - AMP * 10;
	else if (SETUP.key == R_KEY)
		CAM->fov = CAM->fov + AMP * 2;
	else if (SETUP.key == F_KEY)
		CAM->fov = CAM->fov - AMP * 2;
}

static void	ft_print_cam_2(t_setup *setup)
{
	char	*tmp;

	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 100, 16777215, CANGZ_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 100, 16777215,\
			tmp = ft_ftoa((int)(57.3 * CAM->rot->z)));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 120, 16777215, CFOV_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 120, 16777215,\
			tmp = ft_ftoa(CAM->fov));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 140, 16777215, CSCALE_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 140, 16777215,\
			tmp = ft_ftoa(CAM->scale));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 160, 16777215, CLMODE_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 160, 16777215,\
			tmp = ft_itoa(setup->line));
	free(tmp);
}

void		ft_print_cam(t_setup *setup)
{
	char	*tmp;

	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 0, 16777215, CPOSX_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 0, 16777215, \
			tmp = ft_ftoa(CAM->pos->x));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 20, 16777215, CPOSY_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 20, 16777215, \
			tmp = ft_ftoa(CAM->pos->y));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 40, 16777215, CPOSZ_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 40, 16777215, \
			tmp = ft_ftoa(CAM->pos->z));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 60, 16777215, CANGX_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 60, 16777215, \
			tmp = ft_ftoa((int)(57.3 * CAM->rot->x)));
	free(tmp);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, 0, 80, 16777215, CANGY_S);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, setup->width / 5, 80, 16777215, \
			tmp = ft_ftoa((int)(57.3 * CAM->rot->y)));
	free(tmp);
	ft_print_cam_2(setup);
}
