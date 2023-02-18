/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 04:43:50 by lkrabbe          ###   ########.fr       */
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
	printf("\nx before %f y %f\n",array[X],array[Y]);
	printf("degree %f\n",move->direction);
	// printf(" %f %f = %f &  %f %f = %f\n",array[X] , cos(move->direction),array[X] * cos(move->direction),\
	array[Y] , sin(move->direction),array[Y] * sin(move->direction));
	x = array[X] * cos(move->direction) - array[Y] * sin(move->direction);
	y = array[X] * sin(move->direction) + array[Y] * cos(move->direction);
	printf("x after %f y %f\n",x,y);
	move->tile_x += x;
	move->tile_y += y;
}

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
	static double	delta_time = 0.09;

	movement[X] = 0;
	movement[Y] = 0;
	move->velocity = 0.005;
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
	if (delta_time > 0.4)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_E))
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
	// move->direction += 0.02;
	// printf("??diretion %f",move->direction);
	// printf("!>%f %f\n",movement[X],movement[Y]);
	matrix_movement(move, movement);	
	// printf("?>%f %f\n",movement[X],movement[Y]);
	// printf("<%f %f>\n",move->tile_x,move->tile_y);
	// move->tile_x += movement[X];
	// move->tile_y += movement[Y];
	// printf("<!%f %f>\n",move->tile_x,move->tile_y);
	//move->velocity = 0.080;
}
