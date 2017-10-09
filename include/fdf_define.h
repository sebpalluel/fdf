/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 17:21:53 by psebasti         ###   ########.fr       */
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

# define MAX_SIZE		100000
# define MG_MIN_SIZE	3
# define MG_MAX_SIZE	2000
# define MG_MIN_INT		-100
# define MG_MAX_INT		100

# define SETUP			setup[0]
# define S_WIDTH		setup[0].width
# define S_HEIGHT		setup[0].height
# define MAP			setup[0].map
# define M_WIDTH		setup[0].map->width
# define M_HEIGHT		setup[0].map->height
# define M_DEPTH		setup[0].map->depth
# define LERP_IN		setup[0].map->lerp_in
# define LERP_OUT		setup[0].map->lerp_out
# define CLR			setup[0].map->curr_clr
# define MAPG			setup[0].map_gen
# define MG_WIDTH		setup[0].map_gen->mapsize[0]
# define MG_HEIGHT		setup[0].map_gen->mapsize[1]
# define MG_PATH		setup[0].map_gen->path
# define CAM			setup[0].cam
# define MLX			setup[0].mlx
# define IMG			setup[0].img
# define FD				setup[0].fd
# define M_ROT_X		tmp_mat[0]
# define M_ROT_Y		tmp_mat[1]
# define M_ROT_Z		tmp_mat[2]
# define M_ROT_ZY		tmp_mat[3]
# define M_ROT_ZYX		tmp_mat[4]
# define M_TRANS		tmp_mat[5]

# define STATE_RUN		0
# define STATE_START	1
# define STATE_GEN		2
# define STATE_SAVE		3
# define STATE_OPEN		4
# define STATE_DRAW		5

# define DEPTH_ERROR_S	"error: min_depth > max_depth or depth < -100"
# define DEPTH_ERROR2_S	"or depth < -100 || depth > 100"
# define DIM_ERROR_S	"error: width or height > 2000 || < 3"
# define MAP_ERROR_S	"error: map is not in the correct format"
# define FILE_ERROR_S	"error: file doesn't exist"
# define COLOR_ERROR	-1
# define MAP_ERROR		-2
# define DIM_ERROR		-3
# define DEPTH_ERROR	-4
# define FILE_ERROR		-5

# define CPOSX_S		" key LEFT/RIGHT    cam pos x:"
# define CPOSY_S		" key UP/DOWN       cam pos y:"
# define CPOSZ_S		" key DOT/SLASH     cam pos z:"
# define CANGX_S		" key A/D           cam ang x:"
# define CANGY_S		" key S/W           cam ang y:"
# define CANGZ_S		" key Q/E           cam ang z:"
# define CFOV_S			" key F/R           cam fov:"
# define CSCALE_S		" key MINUS/EQUAL   cam scale:"
# define CLMODE_S		" key L             line mode:"

# define START_STR		"FdF by psebasti"
# define ENTER_STR		"Press ENTER to start"
# define MAPG_STR		"MAP GENERATOR MODE"
# define WIDTHG_STR		"TYPE WIDTH OF MAP [ >= 3 && <= 2000] AND PRESS ENTER"
# define HEIGHTG_STR	"TYPE HEIGHT OF MAP [ >= 3 && <= 2000] AND PRESS ENTER"
# define MINDEPTHG_STR	"TYPE MIN DEPTH [ >= -100 && <= 100] AND PRESS ENTER"
# define MAXDEPTHG_STR	"TYPE MAX DEPTH [ >= -100 && <= 100] AND PRESS ENTER"
# define SAVE_STR		"WOULD YOU LIKE TO SAVE IT ?"
# define YESORNO_STR	"y / n"
# define NAME_STR		"TYPE A NAME FOR THIS FILE AND PRESS ENTER"

#endif
