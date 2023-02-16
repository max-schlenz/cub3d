/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:19:38 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/15 23:27:42 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


void draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_memset_cub(int *b, uint32_t c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		draw_pixel((uint8_t *)&b[i++], c);
}

mlx_image_t	*create_background_layer(mlx_t *mlx, int color_ceiling, int color_floor)
{
	mlx_image_t	*img_bg;

	img_bg = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset_cub((int *)img_bg->pixels,
		color_ceiling, WIDTH * HEIGHT / 2);
	ft_memset_cub((int *)img_bg->pixels + (WIDTH * HEIGHT) / 2,
		color_floor, WIDTH * HEIGHT / 2);
	return (img_bg);
}
