/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:51:21 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/21 16:08:47 by psebasti         ###   ########.fr       */
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
int		ft_read_map(t_setup *setup, int fd);
int		ft_setup(t_setup *setup, char **argv, int argc, int allocate);
void	ft_delete_setup(t_setup *setup);
t_vec3	*new_vec3(double x, double y, double z);

#endif
