/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:20:58 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/06 15:23:55 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

# define PI_TIMES_TWO 6.28318530718



void	overshot_protection(t_movement *move)
{
		move->direction -= PI_TIMES_TWO;
	while (move->direction < 0)
		move->direction += PI_TIMES_TWO;
	while (move->top_down > PI_TIMES_TWO)
		move->top_down -= PI_TIMES_TWO;
	while (move->top_down < 0)
		move->top_down += PI_TIMES_TWO;
}

void	mouse_checker(mlx_t *mlx, t_movement *move)
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
		move->top_down += move->rotation_speed;
	}
	else if ((mlx->height / 2 - y) > 0)//? maybe not used in the end
	{
		move->top_down -= move->rotation_speed;
	}
	overshot_protection(move);
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
}
