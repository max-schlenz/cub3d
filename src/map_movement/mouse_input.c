/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:20:58 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/15 23:15:49 by mschlenz         ###   ########.fr       */
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
		move->direction += move->rotation_speed;// coud be based on a factor so it rotates faster
	else if ((mlx->width / 2 - x) > 0)
		move->direction -= move->rotation_speed;
	overshot_protection(&(move->direction));
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
}
