/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/07 20:18:52 by mschlenz         ###   ########.fr       */
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
	printf("player%i %i\n", x, y);
	show_player_anim(sprite->player, img, x, y);
	// draw_player_char(img, y, x);// here texture
}

# define pixel_per_y (int)(y /((double)img->height / (map->height)))
# define pixel_per_x (int)(x /((double)img->width / map->width))

void	draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			if (map->elem[pixel_per_y][pixel_per_x] == '1')
				mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			else if (map->elem[pixel_per_y][pixel_per_x] == '0')
				mlx_put_pixel(img, x, y, MLX_COLOR_DARKSALMON);
			else if (map->elem[pixel_per_y][pixel_per_x] == 'N')
				mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player_on_map(map, img, move, tex, sprite);
}
