/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:25:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/04 14:19:33 by psebasti         ###   ########.fr       */
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

typedef struct		s_map_gen
{
	char			dim[2][MAX_INT_DECIMAL + 1];
	size_t			dim_i[2];
	size_t			dim_t[2];
	size_t			yes_t;
	size_t			name_t;
	size_t			name_i;
	int				mapsize[2];
	float			mid[2];
	int				**map;
}					t_map_gen;

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
	size_t			mode;
	t_mlx			*mlx;
	t_map			*map;
	t_map_gen		*map_gen;
	t_cam			*cam;
	t_img			*img;
}					t_setup;

#endif
