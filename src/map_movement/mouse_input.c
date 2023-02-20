/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:20:58 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/20 14:20:17 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	overshot_protection(double *degree)
{
	while (*degree > PI_TIMES_TWO)
		*degree -= PI_TIMES_TWO;
	while (*degree < 0)
		*degree += PI_TIMES_TWO;
}

void	mouse_checker(mlx_t *mlx, t_movement *move)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if ((mlx->width / 2 - x) < 0)
		move->direction += move->rotation_speed;
	else if ((mlx->width / 2 - x) > 0)
		move->direction -= move->rotation_speed;
	overshot_protection(&(move->direction));
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
}
