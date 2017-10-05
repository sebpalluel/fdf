/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:46:10 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/05 13:18:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void		ft_random_map(t_setup *setup)
{
	int			width;
	int			height;

	height = -1;
	while (++height < MG_HEIGHT)
	{
		width = -1;
		while (++width < MG_WIDTH)
			MAPG->map[height][width] = ft_random(0, MAPG->depth[0], \
					MAPG->depth[1]);
	}
}

static void		ft_convertmap_to_str(t_setup *setup)
{
	int			width[2];
	int			height;
	char		*tmp;

	height = -1;
	while (++height < MG_HEIGHT)
	{
		width[0] = -1;
		width[1] = 0;
		while (++width[0] < MG_WIDTH)
		{
			MAPG->map_str[height][width[1]] = \
			ft_itoa(MAPG->map[height][width[0]]);
			width[1]++;
			tmp = ft_strnew(1);
			*tmp = ' ';
			MAPG->map_str[height][width[1]] = tmp;
			width[1]++;
		}
		tmp = ft_strnew(1);
		*tmp = '\n';
		MAPG->map_str[height][width[1]] = tmp;
	}
}

size_t			ft_generate_map(t_setup *setup)
{
	srand(time(NULL));
	if (!(MAPG->map_str = ft_tab3newstr(MG_WIDTH * 2 + 1, MG_HEIGHT))) // for with complete with num char + ' '
		return (ERROR);
	if (!(MAPG->map = ft_tabnewint(MG_WIDTH, MG_HEIGHT)))
		return (ERROR);
	ft_random_map(setup);
	ft_convertmap_to_str(setup);
	printf("print array int :\n");
	ft_printintarray(MAPG->map, MG_WIDTH, MG_HEIGHT);
	SETUP.mode = STATE_SAVE;
	return (OK);
}
