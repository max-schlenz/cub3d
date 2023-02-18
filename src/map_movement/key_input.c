/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 07:51:24 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	toggle_door(t_movement *move, t_map *map, double delta_time)
{
	int				i;
	char			*elem[4];

	elem[0] = &map->elem[move->y - 1][move->x];
	elem[1] = &map->elem[move->y + 1][move->x];
	elem[2] = &map->elem[move->y][move->x - 1];
	elem[3] = &map->elem[move->y][move->x + 1];
	i = 0;
	while (i < 4)
	{
		if (*(elem[i]) == 'D')
			*(elem[i]) = 'd';
		else if (*(elem[i]) == 'd')
			*(elem[i]) = 'D';
		i++;
	}
	return (0);
}

void	easy_move(double *movement, t_movement *move, double dir)
{
	movement[X] -= move->velocity * cos(move->direction + dir);
	movement[Y] += move->velocity * sin(move->direction + dir);
}

void	wasd_keys(t_movement *move, mlx_t *mlx)
{
	double	movement[2];

	movement[X] = 0;
	movement[Y] = 0;
	move->velocity = 0.05;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		move->velocity *= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		easy_move(movement, move, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		easy_move(movement, move, -M_PI_2);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		easy_move(movement, move, M_PI);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		easy_move(movement, move, M_PI_2);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
}

void	arrow_keys(mlx_t *mlx, t_map *map, t_movement *move)
{	
	static double	delta_time = 0.09;

	delta_time += mlx->delta_time;
	if (delta_time > 0.4)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_E) || \
		mlx_is_key_down(mlx, MLX_KEY_KP_0))
			delta_time = toggle_door(move, map, mlx->delta_time);
		else if (mlx_is_key_down(mlx, MLX_KEY_UP))
			delta_time = front_tile(map, move);
		else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
			delta_time = back_tile(map, move);
		else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			delta_time = left_turn(move);
		else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			delta_time = right_turn(move);
	}
}

void	key_checker(mlx_t *mlx, t_movement *move, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	arrow_keys(mlx, map, move);
	wasd_keys(move, mlx);
}
