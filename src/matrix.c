/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:50:52 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/28 17:07:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_vec3		*ft_new_vec3(double x, double y, double z)
{
	t_vec3		*vec3 = NULL;

	if ((vec3 = (t_vec3*)malloc(sizeof(t_vec3))))
	{
		vec3->x = x;
		vec3->y = y;
		vec3->z = z;
	}
	return (vec3);
}

void		ft_populate_vec3(t_vec3 *to_vec3, double x, double y, double z)
{
	if (to_vec3)
	{
		to_vec3->x = x;
		to_vec3->y = y;
		to_vec3->z = z;
	}
}

double		**ft_matrix_zero(int size)
{
	double	**ret = NULL;
	int		xy[2];

	if (!(ret = (double**)malloc(sizeof(double*) * size + 1)))
		return (NULL);
	xy[0] = -1;
	while (++xy[0] < size)
	{
		xy[1] = -1;
		if (!(ret[xy[0]] = (double*)malloc(sizeof(double) * size)))
			return (NULL);
		while (++xy[1] < size)
			ret[xy[0]][xy[1]] = 0;
	}
	ret[size] = NULL;
	return (ret);
}

void		ft_matrix_translate(double **ret, t_vec3 *vec)
{
	if (ret && vec)
	{
		ret[0][0] = 1;
		ret[1][1] = 1;
		ret[2][2] = 1;
		ret[3][3] = 1;
		ret[0][3] = vec->x;
		ret[1][3] = vec->y;
		ret[2][3] = vec->z;
	}
}

void		ft_matrix_homothety(double **ret, int factor)
{

	if (ret)
	{
		ret[0][0] = factor;
		ret[1][1] = factor;
		ret[2][2] = factor;
		ret[3][3] = 1;
	}
}

void		ft_matrix_mult(double **ret, double **m, double **n, int size)
{
	double	temp;
	int		xyz[3];

	if (ret && m && n)
	{
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
	}
}

void		ft_matrix_add(double **ret, double **m, double **n, int size)
{
	int		xy[2];

	if (ret && m && n)
	{
		xy[0] = -1;
		while (++xy[0] < size)
		{
			xy[1] = -1;
			while (++xy[1] < size)
				ret[xy[0]][xy[1]] = m[xy[0]][xy[1]] + n[xy[0]][xy[1]];
		}
	}
}

void		ft_matrix_rot_x(double **ret, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (ret)
	{
		ret[3][3] = 1;
		ret[0][0] = 1;
		ret[1][1] = c;
		ret[1][2] = -s;
		ret[2][1] = s;
		ret[2][2] = c;
	}
}

void		ft_matrix_rot_y(double **ret, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (ret)
	{
		ret[3][3] = 1;
		ret[0][0] = c;
		ret[0][2] = s;
		ret[1][1] = 1;
		ret[2][0] = -s;
		ret[2][2] = c;
	}
}

void		ft_matrix_rot_z(double **ret, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (ret)
	{
		ret[3][3] = 1;
		ret[2][2] = 1;
		ret[0][0] = c;
		ret[0][1] = -s;
		ret[1][0] = s;
		ret[1][1] = c;
	}
}

void		ft_matrix_on_point(double **m, t_vec3 *vec3)
{
	if (m && vec3)
	{
		vec3->x = m[0][0] * vec3->x
			+ m[0][1] * vec3->y
			+ m[0][2] * vec3->z + m[0][3];
		vec3->y = m[1][0] * vec3->x
			+ m[1][1] * vec3->y
			+ m[1][2] * vec3->z + m[1][3];
		vec3->z = m[2][0] * vec3->x
			+ m[2][1] * vec3->y
			+ m[1][2] * vec3->z + m[2][3];
	}
}
