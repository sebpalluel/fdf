/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/09 21:20:48 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINE_H
# define FDF_DEFINE_H

# define WIDTH		1700
# define HEIGHT		800

# define STEP		5
# define ENDIAN		0
# define BBP		8

# define ESC		53
# define LEFT		123
# define RIGHT		124
# define UP			126
# define DOWN		125
# define MINUS		78
# define PLUS		69
# define CTRL		8
# define STAR		67
# define SLASH		75

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
# define CAM		setup->cam
# define MLX		setup->mlx
# define IMG		setup->img

#endif
