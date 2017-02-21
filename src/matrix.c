/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:50:52 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 18:40:33 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double		**ft_matrix_zero(int size)
{
	double	**ret;
	int		xy[2];

	ret = (double**)malloc(sizeof(double*) * size);
	xy[0] = -1;
	while (++xy[0] < size)
	{
		xy[1] = -1;
		ret[xy[0]] = (double*)malloc(sizeof(double) * size);
		while (++xy[1] < size)
			ret[xy[0]][xy[1]] = 0;
	}
	return (ret);
}

double		**ft_matrix_translate(t_vec3 *vector)
{
	double	**ret;

	ret = ft_matrix_zero(4);
	ret[0][0] = 1;
	ret[1][1] = 1;
	ret[2][2] = 1;
	ret[3][3] = 1;
	ret[0][3] = vector->x;
	ret[1][3] = vector->y;
	ret[2][3] = vector->z;
	return (ret);
}

double		**ft_matrix_homothety(int factor)
{
	double	**ret;

	ret = ft_matrix_zero(4);
	ret[0][0] = factor;
	ret[1][1] = factor;
	ret[2][2] = factor;
	ret[3][3] = 1;
	return (ret);
}

double		**ft_matrix_mult(double **m, double **n, int size)
{
	double	**ret;
	double	temp;
	int		xyz[3];

	ret = ft_matrix_zero(size);
	xyz[0] = -1;
	while (++xyz[0] < size)
	{
		xyz[1] = -1;
		while (++xyz[1] < size)
		{
			temp = 0;
			xyz[2] = -1;
			while (++xyz[2] < size)
				temp = temp + m[xyz[0]][xyz[2]] * n[xyz[2]][xyz[1]];
			ret[xyz[0]][xyz[1]] = temp;
		}
	}
	free(xyz);
	return (ret);
}

double		**ft_matrix_add(double **m, double **n, int size)
{
	double	**ret;
	int		xy[2];

	ret = ft_matrix_zero(size);
	xy[0] = -1;
	while (++xy[0] < size)
	{
		xy[1] = -1;
		while (++xy[1] < size)
			ret[xy[0]][xy[1]] = m[xy[0]][xy[1]] + n[xy[0]][xy[1]];
	}
	return (ret);
}
