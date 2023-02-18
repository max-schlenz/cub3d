/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:11:39 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 04:40:27 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

int	left_turn(t_movement *move)
{
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	if (move->direction < M_PI_2)
		move->direction = M_PI_2 + M_PI;
	else if(move->direction < M_PI)
		move->direction = 0;
	else if(move->direction < M_PI + M_PI_2)
		move->direction = M_PI_2;
	else
		move->direction = M_PI;
	return (0);
}

int	right_turn(t_movement *move)
{
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	if (move->direction < M_PI_2)
		move->direction = M_PI_2;
	else if(move->direction < M_PI)
		move->direction = M_PI;
	else if(move->direction < M_PI + M_PI_2)
		move->direction = M_PI_2 + M_PI;
	else
		move->direction = 0;
	return (0);
}


void	try_to_move(t_map *map, t_movement *move, int x, int y)
{
	if (map->elem[move->y + y][move->x + x] != '1')
	{
		if (map->elem[move->y + y][move->x + x] != 'D')
		{
			move->y += y;
			move->x += x;
		}
	}
}

int	front_tile(t_map *map, t_movement *move)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	if (move->direction < M_PI_2)
		x = -1;
	else if(move->direction < M_PI)
		y = 1;
	else if(move->direction < M_PI + M_PI_2)
		x = 1;
	else
		y =-1;
	try_to_move(map, move, x, y);
	return (0);
}

int	back_tile(t_map *map, t_movement *move)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	if (move->direction < M_PI_2)
		x = 1;
	else if(move->direction < M_PI)
		y = -1;
	else if(move->direction < M_PI + M_PI_2)
		x = -1;
	else
		y = 1;
	try_to_move(map, move, x, y);
	return (0);
}