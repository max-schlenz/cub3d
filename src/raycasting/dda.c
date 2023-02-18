/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 06:32:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 07:43:54 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	dda_info_h(int x, double direction, double *player, t_dda *dda_info)
{
	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
	{
		dda_info->hit[X] = x + 1;
		dda_info->offset = 0;
		dda_info->jump = -1 * tan(direction);
		dda_info->dir = 1;
	}
	else
	{
		dda_info->hit[X] = x;
		dda_info->offset = -1;
		dda_info->dir = -1;
		dda_info->jump = 1 * tan(direction);
	}
	dda_info->hit[Y] = player[Y] + \
	(player[X] - dda_info->hit[X]) * tan (direction);
}

void	dda_info_v(int y, double direction, double *player, t_dda *dda_info)
{
	if (direction >= 0 && direction < M_PI)
	{
		dda_info->hit[Y] = y + 1;
		dda_info->offset = 0;
		dda_info->jump = -1 / tan(direction);
		dda_info->dir = 1;
	}
	else
	{
		dda_info->hit[Y] = y;
		dda_info->offset = -1;
		dda_info->dir = -1;
		dda_info->jump = 1 / tan(direction);
	}
	dda_info->hit[X] = player[X] + \
	(player[Y] - dda_info->hit[Y]) / tan (direction);
}

int	usedda_h(t_dda *dda_info, t_map *map)
{
	while (dda_info->hit[Y] >= 0 \
	&& dda_info->hit[Y] < map->height \
	&& dda_info->hit[X] >= 0 \
	&& dda_info->hit[X] < map->width \
	&& map->elem[(int)dda_info->hit[Y]] \
	[(int)dda_info->hit[X] + dda_info->offset] == '0')
	{
		dda_info->hit[X] += dda_info->dir;
		dda_info->hit[Y] += dda_info->jump;
	}
	return (1);
}

int	usedda_v(t_dda *dda_info, t_map *map)
{
	while (dda_info->hit[Y] >= 0 \
	&& dda_info->hit[Y] < map->height \
	&& dda_info->hit[X] >= 0 \
	&& dda_info->hit[X] < map->width \
	&& map->elem[(int)dda_info->hit[Y] + dda_info->offset] \
	[(int)dda_info->hit[X]] == '0')
	{
		dda_info->hit[Y] += dda_info->dir;
		dda_info->hit[X] += dda_info->jump;
	}
	return (1);
}

int	usedda_ultra(t_dda *dda_h, t_dda *dda_v, t_map *map)
{
	int	hit_h;
	int	hit_v;

	hit_h = 0;
	hit_v = 0;
	while (hit_v == 0 || hit_h == 0)
	{
		hit_h = usedda_h(dda_h, map);
		hit_v = usedda_v(dda_v, map);
		if (hit_h < 0)
		{
			hit_h = 0;
			dda_h->hit[X] += dda_h->dir;
			dda_h->hit[Y] += dda_h->jump;
		}
		if (hit_v < 0)
		{
			hit_v = 0;
			dda_v->hit[Y] += dda_v->dir;
			dda_v->hit[X] += dda_v->jump;
		}
	}
	return (hit_v + hit_h);
}
