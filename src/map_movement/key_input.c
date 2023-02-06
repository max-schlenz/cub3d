/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/06 15:15:41 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

#define X 0
#define Y 1



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
	if (array[X] || array[Y])
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
	matrix_movement(move, movement);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
}