/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/09 17:14:42 by mschlenz         ###   ########.fr       */
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

// void	draw_hori(mlx_image_t *img, int y)
// {
// 	int	i;

// 	i = 0;
// 	while (i < img->width)
// 	{
// 		mlx_put_pixel(img, i, y, MLX_COLOR_BLACK);
// 		i++;
// 	}
// }

// void	draw_vert(mlx_image_t *img, int x)
// {
// 	int	i;

// 	i = 0;
// 	if (x < img->width && x >= 0)
// 		while (i < img->width)
// 		{
// 			mlx_put_pixel(img, x, i, MLX_COLOR_BLACK);
// 			i++;
// 		}
// 	else
// 		printf("x = %i is outside\n",x);
// }


//A.x = Px + (Py-A.y)/tan(ALPHA);
void	show_player_anim(mlx_texture_t **player, mlx_image_t *img, int x, int y)
{
	static int	j = 0;
	
	mlx_draw_texture(img, player[j], x, y);
	j++;
	if (j == 33)
		j = 0;
}

void line(int color,mlx_image_t *img, int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
		if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height)
      	  mlx_put_pixel(img, x0, y0, color);
		else
			return;
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

# define LOGICY y_hit[Y] >= 0 && y_hit[Y] < map->height && y_hit[X] >= 0 && y_hit[X] < map->width
# define LOGICX x_hit[Y] >= 0 && x_hit[Y] < map->height && x_hit[X] >= 0 && x_hit[X] < map->width


void	hori_check(t_movement *move, t_map *map, double *x_hit, double *player, double direction)
{
	double	ya;

	if (direction >= M_PI || direction <= M_PI * 2)
		x_hit[X] = move->x;
	else
		x_hit[X] = move->x + 1;
	x_hit[Y] = player[Y] + (player[X] - x_hit[X]) \
	/ tan(direction - M_PI_2);
	ya = 1 / tan(move->direction - M_PI_2);
	printf("hori%f %f\n",x_hit[Y],x_hit[X]);
	if (direction >= M_PI || direction <= M_PI_2)
	{
		while (LOGICX && (map->elem[(int)x_hit[Y]][(int)x_hit[X] - 1] != '1'))
		{
			x_hit[X] += -1;
			x_hit[Y] += ya;
		}
	}
	else
	{
		while (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X]] != '1')
		{
			x_hit[X] += 1;
			x_hit[Y] += -ya;
		}
	}
}

void	vert_check(t_movement *move, t_map *map, double *y_hit, double *player, double direction)
{
	double	xa;

	if (direction <= M_PI_2 || direction >= M_PI_2 + M_PI)
		y_hit[Y] = move->y;
	else
		y_hit[Y] = move->y + 1;
	y_hit[X] = player[X] + (player[Y] - y_hit[Y]) \
	/ tan(-1 * direction - M_PI_2);
	xa = 1 / tan(-1 * move->direction - M_PI_2);
	// printf("vert%f %f\n",y_hit[Y],y_hit[X]);
	if (direction <= M_PI_2 || direction >= M_PI_2 + M_PI)
	{
		while (LOGICY && (map->elem[(int)y_hit[Y] - 1][(int)y_hit[X]] != '1'))
		{
			y_hit[Y] += -1;
			y_hit[X] += xa;
		}
	}
	else
	{
		while (LOGICY && map->elem[(int)y_hit[Y]][(int)y_hit[X]] != '1')
		{
			y_hit[Y] += 1;
			y_hit[X] += -xa;
		}
	}
}

double	sinlgle_ray(mlx_image_t *img, t_movement *move, t_map *map, double direction)
{
	double	hori[2];
	double	vert[2];
	double	player[2];
	double	len[0];

	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	// hori_check(move, map, hori, player, direction);
	// printf("H%f %f\n", hori[X], hori[Y]);
	// len[0] = fabs((player[X] - hori[X]) / cos(-1 * direction - M_PI_2));
	vert_check(move, map, vert, player, direction);
	// printf("V%f %f\n", vert[X], vert[Y]);
	len[1] = fabs((player[X] - vert[X]) / cos(-1 * direction - M_PI_2));
	line(MLX_COLOR_BISQUE ,img, player[X] * img->width/ map->width, player[Y] * img->height/ map->height, vert[X] * img->width/ map->width, vert[Y] * img->height/ map->height);
	//printf("len 0 %f len 1 %f\n", len[0], len[1]);
	// if (len[1] < len[0])
		// line(MLX_COLOR_SEAGREEN,img, player[X] * img->width/ map->width, player[Y] * img->height/ map->height, hori[X] * img->width/ map->width, hori[Y] * img->height/ map->height);
	// else
	return (0);
}

#define	DEGREE_TO_RADIAL(degree) ((double)(degree) / 360 * (M_PI * 2))
#define	RADIAL_TO_DEGREE(degree) ((double)(degree) * 360 / (M_PI * 2))

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
{
	double	i;
	double	pov;
	double	degree_per_pixel;
	double	degree;
	
	pov =  DEGREE_TO_RADIAL(90);
	degree = move->direction - (pov / 2);
	
	degree_per_pixel = pov / img->width;
	i = 0;
	while(i < img->width)
	{
		overshot_protection(&degree);
		// printf("degree = %f add %f\n", degree, degree_per_pixel);
		sinlgle_ray(img, move, map, degree);
		degree += degree_per_pixel;
		i++;
		// sleep(1);
	}
}
