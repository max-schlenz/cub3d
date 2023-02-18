/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:20:58 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 07:51:13 by lkrabbe          ###   ########.fr       */
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

void	mouse_checker(mlx_t *mlx, t_movement *move, mlx_image_t *img_bg)
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
