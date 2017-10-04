/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/04 15:41:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINE_H
# define FDF_DEFINE_H

# define WIDTH			1920
# define HEIGHT			1080

# define MAX_STEP		400
# define STEP			10
# define AMP			20
# define ENDIAN			0
# define BBP			32

# define BLUE			0x0000FF
# define GREEN			0x00F611
# define BROWN			0x541919
# define WHITE			0xFFFFFF

# define MAX_SIZE		100000
# define M_MIN_SIZE		3
# define M_MAX_SIZE		100000

# define SETUP			setup[0]
# define S_WIDTH		setup[0].width
# define S_HEIGHT		setup[0].height
# define MAP			setup[0].map
# define M_HEIGHT		setup[0].map->height
# define M_DEPTH		setup[0].map->depth
# define LERP_IN		setup[0].map->lerp_in
# define LERP_OUT		setup[0].map->lerp_out
# define CLR			setup[0].map->curr_clr
# define MAPG			setup[0].map_gen
# define MG_WIDTH		setup[0].map->mapsize[0]
# define MG_HEIGHT		setup[0].map->mapsize[1]
# define MG_DEPTH		setup[0].map->depth
# define MG_PATH		setup[0].map_gen->path
# define CAM			setup[0].cam
# define MLX			setup[0].mlx
# define IMG			setup[0].img
# define FD				setup[0].fd
//# define MAT			setup->cam->matrix

# define STATE_RUN		0
# define STATE_START	1
# define STATE_GEN		2
# define STATE_SAVE		3
# define STATE_OPEN		4
# define STATE_DRAW		5

# define CPOSX_S		" key LEFT/RIGHT    cam pos x:"
# define CPOSY_S		" key UP/DOWN       cam pos y:"
# define CPOSZ_S		" key DOT/SLASH     cam pos z:"
# define CANGX_S		" key A/D           cam ang x:"
# define CANGY_S		" key S/W           cam ang y:"
# define CANGZ_S		" key Q/E           cam ang z:"
# define CFOV_S			" key F/R           cam fov:"
# define CSCALE_S		" key MINUS/EQUAL   cam scale:"
# define CLMODE_S		" key L             line mode:"

#endif
