/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/08 11:16:25 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>
/*
void	dots(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_input *map, double x_ofset, double y_ofset)
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

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_input *map)
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
	if (x < img->width && x >= 0)
		while (i < img->width)
		{
			mlx_put_pixel(img, x, i, MLX_COLOR_BLACK);
			i++;
		}
	else
		printf("x = %i is outside\n",x);
}


//A.x = Px + (Py-A.y)/tan(ALPHA);
void	show_player_anim(mlx_texture_t **player, mlx_image_t *img, int x, int y)
{
	static int	j = 0;
	
	mlx_draw_texture(img, player[j], x, y);
	j++;
	if (j == 33)
		j = 0;
}

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
{
	double	player[2];
	double	A[2];

	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	if (move->direction <= M_PI_2 || move->direction >= M_PI_2 + M_PI)
		A[Y] = move->y;
	else
		A[Y] = move->y + 1;
	A[X] = player[X] + (player[Y] - A[Y])/tan(move->direction) ;
	printf("move->d %f A[x] = %f A[y] = %f\n", move->direction, A[X], A[Y]);
	if (A[Y] >= 0 && A[Y]< img->height)
		draw_hori(img, A[Y] * img->height / map->height);
	if (A[X] >= 0 && A[X]< img->width && A[X] != INFINITY)
		draw_vert(img, A[X] * img->width / map->width);
}
