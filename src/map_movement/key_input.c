/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/16 17:25:33 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <time.h>

#define X 0
#define Y 1
# define PI_TIMES_TWO 6.28318530718



/**
 * @brief 
 * 
 * x' = xcosθ - ysinθ.
 * y' = xsinθ + ycosθ.
 * 
 */
void	matrix_movement(t_movement *move, double *array)
{
	double	x;
	double	y;

	x = array[X] * cos(move->direction) - array[Y] * sin(move->direction);
	y = array[X] * sin(move->direction) + array[Y] * cos(move->direction);
	array[X] = x;
	array[Y] = y;
}

static void	toggle_door(t_movement *move, t_map *map, double delta_time)
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
}

/**
 * @brief change position based data depending on specific key pressed.
 * also close window for [esc]
 * 
 *! @todo movement needs to care about current direction aka x * cos() and  y * cos()
 * 
 */
void	key_checker(mlx_t *mlx, t_movement *move, t_map *map)
{
	double			movement[2];
	static double	delta_time = 0;
	static double	last_keypress = 0;

	movement[X] = 0;
	movement[Y] = 0;
	delta_time += mlx->delta_time;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		move->velocity *= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		movement[X] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		movement[Y] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		movement[X] += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		movement[Y] += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_E) && delta_time - last_keypress > 0.3)
	{
		toggle_door(move, map, mlx->delta_time);
		last_keypress = delta_time;
	}
	printf("!>%f %f/n\n",move->tile_x,move->tile_y);
	matrix_movement(move, movement);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
	printf("?>%f %f/n\n\n",move->tile_x,move->tile_y);
	move->velocity = 0.080;
}
