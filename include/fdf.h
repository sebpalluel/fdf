/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 12:45:18 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include <errno.h>
# include "../libs/libft/minilibx/mlx.h"
# include "../libs/libft/includes/libft.h"
# include "../include/fdf_struct.h"
# include "../include/fdf_define.h"


#include <stdio.h>
int		ft_color_input(char **argv, int argc, t_setup *setup);
void	ft_mlx_process(t_setup *setup);
int		ft_read_map(t_setup *setup, int fd);
int		ft_parse_line(t_setup *setup, char **tab, int line);
int		ft_free_tmp(char **tab, int fd, int return_val);
t_setup	*ft_setup(char **argv, int argc, int *usage);
t_setup	*ft_delete_setup(t_setup *setup);
int		usage(int mode);
int		ft_update_map_and_cam(t_setup *setup);
void	ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr);
void	ft_give_color(t_setup *setup, t_color *clr, int z);
void	ft_draw_map_point(t_setup *setup);
void	ft_draw_map(t_setup *setup);
void	ft_free_matrix_cam(t_setup *setup);
void	ft_scale_cam(t_setup *setup, int keycode);
void	ft_rot_cam(t_setup *setup, int keycode);
void	ft_orient_cam(t_setup *setup, int keycode);
void	ft_print_cam(t_setup *setup);
int		ft_allocate_map(t_setup *setup);
int		ft_save_map(t_setup *setup);
size_t	ft_name_input(t_setup *setup);
int		ft_configure_dim(t_setup *setup);
size_t	ft_generate_map(t_setup *setup);

#endif
