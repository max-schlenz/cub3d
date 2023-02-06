/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/06 20:52:49 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

/**
 * @brief 
 * 
 * @todo use a sprite for a the payer
 */
void	draw_player_char(mlx_image_t *img, int y, int x)
{
	mlx_put_pixel(img, x, y, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x + 1, y, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x, y + 1, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x + 1, y + 1, MLX_COLOR_BLACK);
}

void	draw_player_on_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	int	x;
	int	y;

	x = move->x * (img->width / map->map_width);
	y = move->y * (img->height / (map->map_height));
	x += move->tile_x * (img->width / (map->map_width));
	y += move->tile_y * (img->height / map->map_height);
	printf("player%i %i\n", x, y);
	draw_player_char(img, y, x);// here texture
}

# define pixel_per_y (int)(y /((double)img->height / (map->map_height)))
# define pixel_per_x (int)(x /((double)img->width / map->map_width))

void	draw_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			if (map->array[pixel_per_y][pixel_per_x] == '1')
				mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			else if (map->array[pixel_per_y][pixel_per_x] == '0')
				mlx_put_pixel(img, x, y, MLX_COLOR_DARKSALMON);
			else if (map->array[pixel_per_y][pixel_per_x] == 'N')
				mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player_on_map(map, img, move);
}
