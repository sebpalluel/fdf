/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 18:06:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include <errno.h>
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include "../include/fdf_struct.h"
# include "../include/fdf_define.h"

int		ft_color_input(t_setup *setup);
void	ft_mlx_process(t_setup *setup);
int		ft_read_map(t_setup *setup);
int		ft_parse_line(t_setup *setup, char **tab, int line);
int		ft_free_tmp(char **tab, int fd, int return_val);
t_setup	*ft_setup(int argc, char **argv, int *usage);
t_setup	*ft_delete_setup(t_setup *setup);
int		usage(int mode);
int		ft_update_map_and_cam(t_setup *setup);
void	ft_put_pix(t_setup *setup, t_pix *pix, t_color *clr);
void	ft_give_color(t_setup *setup, t_color *clr, int z);
void	ft_draw_map_point(t_setup *setup);
void	ft_draw_map(t_setup *setup);
void	ft_free_matrix_cam(t_setup *setup);
void	ft_scale_cam(t_setup *setup);
void	ft_rot_cam(t_setup *setup);
void	ft_orient_cam(t_setup *setup);
void	ft_print_cam(t_setup *setup);
int		ft_allocate_map(t_setup *setup);
int		ft_save_map(t_setup *setup);
size_t	ft_name_input(t_setup *setup);
int		ft_configure_dim(t_setup *setup);
size_t	ft_generate_map(t_setup *setup);
int		ft_setup_menu(t_setup *setup);
void	ft_start(t_setup *setup);
int		ft_configure_depth(t_setup *setup);
int		ft_map_dim(t_setup *setup, size_t *c, char *str, size_t *flag);
int		ft_setup_mode(t_setup *setup, int ret);
int		ft_open_or_gen(t_setup *setup);

#endif
