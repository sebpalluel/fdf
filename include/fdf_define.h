/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/04 14:09:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINE_H
# define FDF_DEFINE_H

# define WIDTH		1920
# define HEIGHT		1080

# define MAX_STEP	400
# define STEP		10
# define AMP		20
# define ENDIAN		0
# define BBP		32

# define ESC		53
# define LEFT		123
# define RIGHT		124
# define DOWN		125
# define UP			126
# define MINUS		27
# define EQUAL		24
# define DOT_KEY	47
# define SLASH_KEY	44
# define CTRL		256
# define STAR		67
# define SLASH		75
# define G_KEY		5
# define W_KEY		13
# define S_KEY		1
# define A_KEY		0
# define D_KEY		2
# define Q_KEY		12
# define E_KEY		14
# define R_KEY		15
# define F_KEY		3
# define L_KEY		37

# define BLUE		0x0000FF
# define GREEN		0x00F611
# define BROWN		0x541919
# define WHITE		0xFFFFFF

# define MAX_SIZE	100000

# define MAP		setup->map
# define M_WIDTH	setup->map->width
# define M_HEIGHT	setup->map->height
# define M_DEPTH	setup->map->depth
# define LERP_IN	setup->map->lerp_in
# define LERP_OUT	setup->map->lerp_out
# define CLR		setup->map->curr_clr
# define CAM		setup->cam
# define MLX		setup->mlx
# define IMG		setup->img
//# define MAT		setup->cam->matrix

#endif
