/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/10 15:02:39 by mschlenz         ###   ########.fr       */
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

void	draw_player_on_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite)
{
	int	x;
	int	y;

	x = move->x * (img->width / map->width);
	y = move->y * (img->height / (map->height));
	x += move->tile_x * (img->width / (map->width));
	y += move->tile_y * (img->height / map->height);
	show_player_anim(sprite->player, img, x, y);
	// draw_player_char(img, y, x);// here texture
}

# define pixel_per_y (int)(y /(pixel_per_tile))
# define pixel_per_x (int)(x /(pixel_per_tile))

void	draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite)
{
	int	x;
	int	y;
	int	pixel_per_tile;

	x = 0;
	y = 0;
	if ((double)img->height / (map->height) > (double)img->width / map->width)
		pixel_per_tile =  (double)img->width / map->width;
	else
		pixel_per_tile =  (double)img->width / map->width;
	while (y < img->height)
	{
		while (x < img->width)
		{
			if (y /(pixel_per_tile) >= map->height|| x /(pixel_per_tile) > map->width)
				mlx_put_pixel(img, x, y, MLX_COLOR_BLACK);
			else
			{
				if (map->elem[pixel_per_y][pixel_per_x] == '1')
					mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
				else if (map->elem[pixel_per_y][pixel_per_x] == '0')
					mlx_put_pixel(img, x, y, MLX_COLOR_DARKSALMON);
				else if (map->elem[pixel_per_y][pixel_per_x] == 'N')
					mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			}
			x++;
		}
		x = 0;
		y++;
	}
	draw_player_on_map(map, img, move, tex, sprite);
}
