/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/12 03:47:32 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

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

/**
 * @brief change position based data depending on specific key pressed.
 * also close window for [esc]
 * 
 *! @todo movement needs to care about current direction aka x * cos() and  y * cos()
 * 
 */
void	key_checker(mlx_t *mlx, t_movement *move)
{
	double	movement[2];

	movement[X] = 0;
	movement[Y] = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		movement[Y] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		movement[X] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		movement[Y] += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		movement[X] += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		move->direction = 0.1 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_2))
		move->direction = 0.2 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_3))
		move->direction = 0.3 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_4))
		move->direction = 0.4 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_5))
		move->direction = 0.5 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_6))
		move->direction = 0.6 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_7))
		move->direction = 0.7 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_8))
		move->direction = 0.8 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_9))
		move->direction = 0.9 * PI_TIMES_TWO;
	if (mlx_is_key_down(mlx, MLX_KEY_0))
		move->direction = 1.0 * PI_TIMES_TWO;
	matrix_movement(move, movement);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
}
