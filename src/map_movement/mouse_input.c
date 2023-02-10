/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:20:58 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/10 16:18:06 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

# define PI_TIMES_TWO 6.28318530718

void	overshot_protection(double *degree)
{
	while (*degree > PI_TIMES_TWO)
		*degree -= PI_TIMES_TWO;
	while (*degree < 0)
		*degree += PI_TIMES_TWO;
}

void	mouse_checker(mlx_t *mlx, t_movement *move, mlx_image_t *img_bg)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if ((mlx->width / 2 - x) < 0)
	{
		move->direction += move->rotation_speed;// coud be based on a factor so it rotates faster
	}
	else if ((mlx->width / 2 - x) > 0)
	{
		move->direction -= move->rotation_speed;
	}
	if ((mlx->height / 2 - y) < 0)//? maybe not used in the end// top down for  tranlate the casting line up or down
	{
		move->top_down += 10;
		img_bg->instances[0].y = move->top_down;
		// bg->instances[0].y += 1;
	}
	else if ((mlx->height / 2 - y) > 0)//? maybe not used in the end
	{
		move->top_down -= 10;
		img_bg->instances[0].y = move->top_down;
	}
	// overshot_protection(&(move->top_down));
	// if (move->top_down > 1)
	// 	move->top_down = 1;
	// else if (move->top_down < 0)
	// 	move->top_down = 0;
	overshot_protection(&(move->direction));
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
}
