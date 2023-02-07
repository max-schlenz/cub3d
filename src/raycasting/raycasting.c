/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/07 14:24:47 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>
/*
void	dots(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_parse *map, double x_ofset, double y_ofset)
{
	int	x;
	int	y;

	x = move->x * (img->width / map->map_width);
	y = move->y * (img->height / (map->map_height));
	x += (move->tile_x + x_ofset) * (img->width / (map->map_width));
	y += (move->tile_y + y_ofset) * (img->height / map->map_height);
	printf(">%i %i\n", x, y);
	if ( x < 0 || y < 0)
		return;
	if ( x > img->width || y > img->height)
		return;
	mlx_put_pixel(img, x , y , MLX_COLOR_BLACK);
}

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_parse *map)
{
	int	dx;
	int	dy;
	//  for direction
	if (move->direction <= M_PI)
		dx = +1;
	else
		dx = -1;
	if (move->direction - M_PI_2 <= M_PI)
		dy = +1;
	else
		dy = -1;

	double	difx;
	double	dify;
	// difrent to first hit with hori or vert line
	difx = dx * move->tile_x;
	dify = dy * move->tile_y;
	// move->direction = move->direction /0
	double	rx;
	double	ry;
	printf("winkel %f\n", move->direction / (2 * M_PI) * 360);
	rx = dify / tan(move->direction);
	ry = difx / tan(move->direction);
	printf("ry %f difx %f\n", ry, difx);
	dots(mlx,img,move,map,difx,ry);
	printf("rx %f dify %f\n", rx, dify);
	dots(mlx,img,move,map,rx,dify);
}
*/

# define X 0
# define Y 1

void	draw_hori(mlx_image_t *img, int y)
{
	int	i;

	i = 0;
	while (i < img->width)
	{
		mlx_put_pixel(img, i, y, MLX_COLOR_BLACK);
		i++;
	}
}

void	draw_vert(mlx_image_t *img, int x)
{
	int	i;

	i = 0;
	while (i < img->width)
	{
		mlx_put_pixel(img, x, i, MLX_COLOR_BLACK);
		i++;
	}
}

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_parse *map, t_texture *tex)
{
	double	player[2];
	double	A[2];

	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	if (move->direction <= M_PI_2 || move->direction >= M_PI_2 + M_PI)
		A[Y] = move->y;
	else
		A[Y] = move->y + 1;
	A[X] = player[X] + move->tile_y + move->y ;
	printf("move->d %f\n", move->direction);
	draw_hori(img, A[Y] * img->height / map->map_height);
	mlx_put_string(mlx, "test", 100, 100);
	mlx_draw_texture(img, tex->player, 50, 100);
}


