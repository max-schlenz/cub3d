/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/12 03:47:00 by mschlenz         ###   ########.fr       */
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

void line(mlx_image_t *img, int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
		if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height)
      	  mlx_put_pixel(img, x0, y0, MLX_COLOR_BLACK);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void	vert_check(t_movement *move, t_map *map, double *A)
{
	double	player[2];
	double	xa;
	int		d;

	if (move->direction <= M_PI_2 || move->direction >= M_PI_2 + M_PI)
	{
		d = 1;
		A[Y] = move->y;
	}
	else
	{
		d = -1;
		A[Y] = move->y + 1;
	}
	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	A[X] = player[X] + (player[Y] - A[Y]) / tan(-1 * move->direction - M_PI_2);
	xa = 1 / tan(-1 * move->direction - M_PI_2);
	while (A[Y] >= 0 && A[Y] < map->height && A[X] >= 0 && A[X] < map->width && map->elem[(int)A[Y] - 1][(int)A[X]] != '1')
	{
		A[Y] += d * -1;
		A[X] += d * xa;
	}
}

void	hori_check(t_movement *move, t_map *map, double *A)
{
	double	player[2];
	double	ya;
	int		d;

	if (move->direction <= M_PI_2 || move->direction >= M_PI_2 + M_PI)
	{
		d = 1;
		A[X] = move->y;
	}
	else
	{
		d = -1;
		A[X] = move->x + 1;
	}
	player[Y] = move->y + move->tile_y;
	player[X] = move->x + move->tile_x;
	A[Y] = player[Y] + (player[X] - A[X]) / tan(-1 * move->direction - M_PI_2);
	ya = 1 / tan(-1 * move->direction - M_PI_2);
	while (A[Y] >= 0 && A[Y] < map->height && A[X] >= 0 && A[X] < map->width && map->elem[(int)A[Y]][(int)A[X] - 1] != '1')
	{
		A[X] += d * -1;
		A[Y] += d * ya;
	}
}

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
{
	double	hori[2];
	double	vert[2];
	double	player[2];

	player[Y] = move->y + move->tile_y;
	player[X] = move->x + move->tile_x;
	hori_check(move, map, hori);
	printf("hori %f %f \n", hori[Y], hori[X]);
	//if (hori[Y] >= 0 && hori[Y] < map->height && hori[X] >= 0 && hori[X] < map->width)
		line(img, player[X],player[Y], hori[X],hori[Y]);
	vert_check(move, map, vert);
	//if (vert[Y] >= 0 && vert[Y] < map->height && vert[X] >= 0 && vert[X] < map->width)
		line(img, player[X],player[Y], vert[X],vert[Y]);
	printf("vert %f %f \n", vert[Y], vert[X]);
// if (A[Y] >= 0 && A[Y] < img->height)
	// 	draw_hori(img, A[Y] * img->height / map->height);
	// if (A[X] >= 0 && A[X] < img->width && A[X] != INFINITY)
	// 	draw_vert(img, A[X] * img->width / map->width);
	// if ((A[Y] >= 0 && A[Y] < img->height && (A[X] >= 0 && A[X] < img->width && A[X] != INFINITY)))
	// 	line(img, player[X]* (img->height / map->height), player[Y]* (img->width / map->width), A[X]* (img->height / map->height), A[Y]* (img->width / map->width));
	
	// if ((A[Y] >= 0 && A[Y] < img->height && (A[X] >= 0 && A[X] < img->width && A[X] != INFINITY)))
	// 	line(img, player[X]* (img->height / map->height), player[Y]* (img->width / map->width), A[X]* (img->height / map->height), A[Y]* (img->width / map->width));
}
