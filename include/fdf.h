/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/07 18:06:26 by psebasti         ###   ########.fr       */
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
# include "../libs/libft/includes/libft.h"
# include "../include/fdf_struct.h"
# include "../include/fdf_define.h"
# include <stdio.h> // warning, erase when finish

int		ft_color_input(char **argv, int argc, t_setup *setup);
t_color	*ft_new_color(unsigned char r, unsigned char g, \
		unsigned char b);
void	ft_mlx_process(t_setup *setup);
int		ft_read_map(t_setup *setup, int fd);
t_setup	*ft_setup(char **argv, int argc, int *usage);
int		usage(int mode);
t_setup	*ft_delete_setup(t_setup *setup);
t_vec3	*ft_new_vec3(double x, double y, double z);
void	ft_populate_vec3(t_vec3 *to_vec3, double x, double y, double z);
t_pix	*ft_new_pix(int x, int y, int z);
void	ft_populate_pix(t_pix *to_pix, int x, int y, int z);
int		ft_update_map_and_cam(t_setup *setup);
void	ft_give_color(t_setup *setup, t_color *clr, int z);
t_color	*ft_hexcolor(int hexValue);
void	ft_hexa_to_color(t_color *col, int hexValue);
void	ft_draw_map_point(t_setup *setup);
void	ft_draw_map(t_setup *setup);
void	ft_clean_img(t_setup *setup);
t_img	*ft_imgnew(void *mlx, size_t x, size_t y);
void	ft_imgdel(t_img *img, void *mlx);
t_mlx	*ft_init_window(char *name, int width, int height);
void	ft_free_matrix_cam(t_setup *setup);
void	ft_scale_cam(t_setup *setup, int keycode);
void	ft_rot_cam(t_setup *setup, int keycode);
void	ft_orient_cam(t_setup *setup, int keycode);
void	ft_print_cam(t_setup *setup);
int		ft_allocate_map(t_setup *setup);

double	**ft_matrix_zero(int size);
void	ft_matrix_translate(double **ret, t_vec3 *vector);
//void	ft_matrix_homothetyt_matrix_translate(t_vec3 *vector);
void	ft_matrix_homothety(double **ret, int factor);
void	ft_matrix_mult(double **ret, double **m, double **n, int size);
void	ft_matrix_add(double **ret, double **m, double **n, int size);
void	ft_matrix_rot_x(double **ret, double deg);
void	ft_matrix_rot_y(double **ret, double deg);
void	ft_matrix_rot_z(double **ret, double deg);
void	ft_matrix_on_point(double **ret, t_vec3 *vec3);

#endif
