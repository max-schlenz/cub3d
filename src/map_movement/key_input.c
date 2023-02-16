/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:04:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/16 00:13:06 by mschlenz         ###   ########.fr       */
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

// static void	toggle_door(t_movement *move, t_map *map)
// {
// 	static int i = 0;
// 	if (map->elem[move->y - 1][move->x] == 'D'			//north
// 		|| map->elem[move->y + 1][move->x] == 'D'		//south
// 		|| map->elem[move->y][move->x - 1] == 'D'		//west
// 		|| map->elem[move->y][move->x + 1] == 'D'		//east
// 		&& map->elem[move->y][move->x] != 'D')
// 		{
// 			printf("DOOR TOGGLED %i\n", i++);
// 		}
// }


/*
y - 1; x - 1
y - 1; x
y - 1; x + 1

*/

#include <time.h>

static void	toggle_door(t_movement *move, t_map *map)
{
	int				i;
	char			*elem[4];
	clock_t			current_time;
	double			time_elapsed;
	static clock_t	last_keypress = 0;
	
	current_time = clock();
	time_elapsed = (double)(current_time - last_keypress) / CLOCKS_PER_SEC;
	elem[0] = &map->elem[move->y - 1][move->x];
	elem[1] = &map->elem[move->y + 1][move->x];
	elem[2] = &map->elem[move->y][move->x - 1];
	elem[3] = &map->elem[move->y][move->x + 1]; 
	i = 0;
	while (i < 4)
	{
		if (time_elapsed >= 0.3)
		{
			if (*(elem[i]) == 'D')
				*(elem[i]) = 'd';
			else if (*(elem[i]) == 'd')
				*(elem[i]) = 'D';
			last_keypress = current_time;
		}
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
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		toggle_door(move, map);
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
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
	{
		move->tmp--;
		printf("%i\n", move->tmp);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
	{
		move->tmp++;
		printf("%i\n", move->tmp);
	}
	matrix_movement(move, movement);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
}
