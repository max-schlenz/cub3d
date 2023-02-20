/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:09:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/20 13:57:01 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	draw_tile(mlx_image_t *img, t_tile *tile, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_TILE_SIZE)
	{
		x = 0;
		while (x < MAP_TILE_SIZE)
		{
			if (x > MAP_TILE_SIZE * (1 - MAP_TILE_BORDER) \
			|| x < MAP_TILE_SIZE * MAP_TILE_BORDER \
			|| y > MAP_TILE_SIZE * (1 - MAP_TILE_BORDER) \
			|| y < MAP_TILE_SIZE * MAP_TILE_BORDER)
				mlx_put_pixel(img, tile->x + x, tile->y + y, MLX_COLOR_WHITE);
			else
				mlx_put_pixel(img, tile->x + x, tile->y + y, color);
			x++;
		}
		y++;
	}
}

int	what_tile(t_map *map, t_movement *move, int x, int y)
{
	if (x == 0 && y == 0)
		return (A_PLAYER);
	x = move->x + x;
	y = move->y + y;
	if (x < 0 || y < 0)
		return (MLX_COLOR_BLANCHEDALMOND);
	if (x >= map->width || y >= map->height)
		return (MLX_COLOR_BLANCHEDALMOND);
	if (map->elem[y][x] == '1')
		return (MLX_COLOR_BURLYWOOD);
	if (map->elem[y][x] == 'd')
		return (A_ODOOR);
	if (map->elem[y][x] == 'D')
		return (A_LDOOR);
	return (MLX_COLOR_PALEVIOLETRED);
}

void	draw_map(t_map *map, mlx_image_t *img, t_movement *move,
	t_sprites *sprites)
{
	int		x;
	int		y;
	t_tile	tile;

	y = -TILE_PER_MAP;
	while (y <= TILE_PER_MAP)
	{
		x = -TILE_PER_MAP;
		while (x <= TILE_PER_MAP)
		{
			tile.color = what_tile(map, move, x, y);
			tile.x = MAP_TILE_SIZE * (x + TILE_PER_MAP);
			tile.y = MAP_TILE_SIZE * (y + TILE_PER_MAP);
			if (tile.color == A_PLAYER
				|| tile.color == A_LDOOR
				|| tile.color == A_ODOOR)
				draw_anim(tile, img, sprites);
			else
				draw_tile(img, &tile, tile.color);
			x++;
		}
		y++;
	}	
	return ;
}
