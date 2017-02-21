/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 15:23:48 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINE_H
# define FDF_DEFINE_H

# define WIDTH		1920
# define HEIGHT		1080

# define ESC		53
# define LEFT		123
# define RIGHT		124
# define UP			126
# define DOWN		125
# define MINUS		78
# define PLUS		69
# define KEY_C		8
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
# define CAM		setup->cam
# define MLX		setup->mlx

#endif
