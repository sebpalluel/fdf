/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:25:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/08/18 17:40:51 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

typedef struct		s_map
{
	int				width;
	int				height;
	int				depth;
	size_t			hexa;
	float			*mid;
	t_color			*lerp_in;
	t_color			*lerp_out;
	t_color			*curr_clr;
	t_pix			*pix;
	int				**tmp_map;
	t_pix			**map;
}					t_map;

typedef struct		s_cam
{
	t_vec3			*pos;
	t_vec3			*rot;
	double			scale;
	double			fov;
	double			offset_x;
	double			offset_y;
	double			***tmp_mat;
	double			**to_cam;
}					t_cam;

typedef struct		s_setup 
{
	unsigned int	width;
	unsigned int	height;
	size_t			ui;
	size_t			line;
	t_mlx			*mlx;
	t_map			*map;
	t_cam			*cam;
	t_img			*img;
}					t_setup;

#endif
