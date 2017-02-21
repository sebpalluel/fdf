/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:25:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 15:56:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_pix
{
	int				x;
	int				y;
	int				z;
}					t_pix;

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
	int				***map3D;
	t_pix			**pix;
}					t_map;

typedef struct		s_cam
{
	t_vec3			*pos;
	t_vec3			*rot;
	double			scale;
	double			fov;
	double			offset_x;
	double			offset_y;
}					t_cam;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_setup 
{
	unsigned int	width;
	unsigned int	height;
	t_color			*lerp_in;
	t_color			*lerp_out;
	t_mlx			*mlx;
	t_map			*map;
	t_cam			*cam;
}					t_setup;

#endif
