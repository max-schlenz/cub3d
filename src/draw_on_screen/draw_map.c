/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/11 19:15:50 by lkrabbe          ###   ########.fr       */
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

typedef struct s_tile{
	int	pixel_per_tile;
	int	x;
	int	y;
	int	color;
}t_tile;

# define MAP_TILE_BORDER 0.1
# define MAP_TILE_SIZE 20
# define TILE_PER_MAP 5
# define TILE_BORDER(X) X > MAP_TILE_SIZE * (1 - MAP_TILE_BORDER) || X < MAP_TILE_SIZE * MAP_TILE_BORDER

void draw_tile(mlx_image_t *img, t_tile *tile)
{
	int	y;
	int	x;
	y = 0;
	while (y < tile->pixel_per_tile)
	{
		x = 0;
		while(x < tile->pixel_per_tile)
		{
			if (TILE_BORDER(x) || TILE_BORDER(y))
				mlx_put_pixel(img , tile->x + x,tile->y + y, MLX_COLOR_WHITE);
			else
				mlx_put_pixel(img , tile->x + x,tile->y + y, tile->color);
			x++;
		}
		y++;
	}
}

int	what_tile(t_map *map, t_movement *move , int x, int y)
{
	if ( x == 0 && y == 0)
		return (MLX_COLOR_RED);
	x = move->x + x;
	y = move->y + y;
	if (x < 0 || y < 0)
		return (MLX_COLOR_BLANCHEDALMOND);
	if (map->elem[y][x] == '1')
		return ( MLX_COLOR_BURLYWOOD);
	// elsif (x <  - MAP_TILE_SIZE / 2 || y < 0)
	// 	return (MLX_COLOR_BLACK);
		return (MLX_COLOR_BLUE);
}

void	draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite)
{
	int	x;
	int	y;
	int	pixel_per_tile;
	t_tile tile;

	tile.pixel_per_tile = MAP_TILE_SIZE;
	y = -TILE_PER_MAP;
	while (y <= TILE_PER_MAP)
	{
		x = -TILE_PER_MAP;
		while ( x <= TILE_PER_MAP)
		{
			tile.color = what_tile(map, move , x , y);
			tile.x = tile.pixel_per_tile  * (x + TILE_PER_MAP);
			tile.y = tile.pixel_per_tile  * (y + TILE_PER_MAP);
			draw_tile(img, &tile);
			x++;
		}
		y++;
	}
	


	return ;
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
