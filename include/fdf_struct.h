/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:25:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/07 21:32:12 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vec3;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_map
{
	int				width;
	int				height;
	int				depth;
	t_vec3			**vec3;
}					t_map;

typedef struct		s_cam
{
	double			x;
	double			y;
	double			scale;
	double			offset_x;
	double			offset_y;
}					t_cam;

typedef struct		s_setup 
{
	unsigned int	width;
	unsigned int	height;
	t_color			*lerp_in;
	t_color			*lerp_out;
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			*map;
	t_cam			*cam;
}					t_setup;

#endif
