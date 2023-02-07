/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:18:12 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/07 19:56:32 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	check_west(t_map *map, t_movement *move)
{
	if (move->tile_x < 0)
	{
		if (wall_check(map, move, 0, -1) == 0)
		{
			move->x--;
			move->tile_x = 1;
		}
		else
		{
			move->tile_x = 0.01;
		}
	}
}

void	check_east(t_map *map, t_movement *move)
{
	if (move->tile_x > 1)
	{
		if (wall_check(map, move, 0, +1) == 0)
		{
			move->x++;
			move->tile_x = 0;
		}
		else
		{
			move->tile_x = 0.99;
		}
	}
}

void	check_north(t_map *map, t_movement *move)
{
	if (move->tile_y < 0)
	{
		if (wall_check(map, move, -1, 0) == 0)
		{
			move->y--;
			move->tile_y = 1;
		}
		else
		{
			move->tile_y = 0.01;
		}
	}
}

void	check_south(t_map *map, t_movement *move)
{
	if (move->tile_y > 1)
	{
		if (wall_check(map, move, +1, 0) == 0)
		{
			move->y++;
			move->tile_y = 0;
		}
		else
		{
			move->tile_y = 0.99;
		}
	}
}

void	is_there_something(t_map *map, t_movement *move)
{
	check_north(map, move);
	check_south(map, move);
	check_east(map, move);
	check_west(map, move);
}
