/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_used_funtions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 06:33:15 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 06:33:38 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3D.h>

void	matrix_two(double *array, double degree)
{
	double	x;
	double	y;

	x = array[0] * cos(degree) - array[1] * sin(degree);
	y = array[0] * sin(degree) + array[1] * cos(degree);
	array[0] = x;
	array[1] = y;
}

void	show_player_anim(mlx_texture_t **player, mlx_image_t *img, int x, int y)
{
	static int	j = 0;

	mlx_draw_texture(img, player[j], x, y);
	j++;
	if (j == 33)
		j = 0;
}
