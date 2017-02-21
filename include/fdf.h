/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 18:58:00 by psebasti         ###   ########.fr       */
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
# include "../get_next_line/get_next_line.h"
# include "../include/fdf_struct.h"
# include "../include/fdf_define.h"

int		ft_color_input(char **argv, int argc, t_setup *setup);
void	ft_mlx_process(t_setup *setup);
int		***ft_read_map(t_setup *setup, int fd);
int		ft_setup(t_setup *setup, char **argv, int argc, int allocate);
void	ft_delete_setup(t_setup *setup);
t_vec3	*ft_new_vec3(double x, double y, double z);
int		ft_populate_map(t_setup *setup, int ***map_tmp);

double		**ft_matrix_zero(int size);
double		**ft_matrix_translate(t_vec3 *vector);
double		**ft_matrix_homothety(int factor);
double		**ft_matrix_mult(double **m, double **n, int size);
double		**ft_matrix_add(double **m, double **n, int size);
double		**ft_matrix_rot_x(double deg);
double		**ft_matrix_rot_y(double deg);
double		**ft_matrix_rot_z(double deg);
void		ft_matrix_on_point(t_vec3 *vec3, double **m);
	
#endif
