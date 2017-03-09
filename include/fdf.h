/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/03/08 16:54:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include <errno.h>
# include "../libs/minilibx/mlx.h"
# include "../libs/libft/libft.h"
# include "../include/fdf_struct.h"
# include "../include/fdf_define.h"
# include <stdio.h> // warning, erase when finish

int		ft_color_input(char **argv, int argc, t_setup *setup);
void	ft_mlx_process(t_setup *setup);
int		ft_read_map(t_setup *setup, int fd);
t_setup	*ft_setup(t_setup *setup, char **argv, int argc, int allocate);
t_setup	*ft_delete_setup(t_setup *setup);
t_vec3	*ft_new_vec3(double x, double y, double z);
t_pix	*ft_new_pix(int x, int y, int z);
int		ft_update_map_and_cam(t_setup *setup);
t_color	*ft_give_color(int z, t_setup *setup);
void	ft_draw_map_point(t_setup *setup);
void	ft_draw_map(t_setup *setup);
t_img	*ft_imgnew(void *mlx, size_t x, size_t y);
t_mlx	*ft_init_window(char *name, int width, int height);

double	**ft_matrix_zero(int size);
double	**ft_matrix_translate(t_vec3 *vector);
double	**ft_matrix_homothetyt_matrix_translate(t_vec3 *vector);
double	**ft_matrix_homothety(int factor);
double	**ft_matrix_mult(double **m, double **n, int size);
double	**ft_matrix_add(double **m, double **n, int size);
double	**ft_matrix_rot_x(double deg);
double	**ft_matrix_rot_y(double deg);
double	**ft_matrix_rot_z(double deg);
void	ft_matrix_on_point(t_vec3 *vec3, double **m);

#endif
