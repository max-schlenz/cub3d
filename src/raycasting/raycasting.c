/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/11 21:18:23 by mschlenz         ###   ########.fr       */
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

void	draw_hori(mlx_image_t *img, int y, uint32_t col)
{
	uint32_t	i;

	i = 0;
	while (i < img->width)
	{
		mlx_put_pixel(img, i, y, col);
		i++;
	}
}

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

	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
		x_hit[X] = move->x + 1;
	else
		x_hit[X] = move->x;
	x_hit[Y] = player[Y] + (player[X] - x_hit[X]) * tan (direction);
	ya = 1 * tan(direction);
	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
	{
		while (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X]] == '0')
		{
			x_hit[X] += 1;
			x_hit[Y] += -ya;
		}
	}
	else
	{
		while (LOGICX && (map->elem[(int)x_hit[Y]][(int)x_hit[X] - 1] == '0'))
		{
			x_hit[X] += -1;
			x_hit[Y] += ya;
		}
	}
}

void	vert_check(t_movement *move, t_map *map, double *y_hit, double *player, double direction)
{
	double	xa;

	if (direction >= 0 && direction < M_PI)
		y_hit[Y] = move->y + 1;
	else
		y_hit[Y] = move->y;
	y_hit[X] = player[X] + (player[Y] - y_hit[Y]) / tan(direction);
	xa = 1 / tan(direction);
	if (direction >= 0 && direction < M_PI)
	{
		while (LOGICY && map->elem[(int)y_hit[Y]][(int)y_hit[X]] == '0')
		{
			y_hit[Y] += 1;
			y_hit[X] += -xa;
		}
	}
	else
	{
		while (LOGICY && (map->elem[(int)y_hit[Y] - 1][(int)y_hit[X]] == '0'))
		{
			y_hit[Y] += -1;
			y_hit[X] += xa;
		}
	}
}

double	sinlgle_ray(t_array *test, t_movement *move, t_map *map, double direction, mlx_image_t *img)
{
	double	hori[3];
	double	vert[3];
	double	player[2];
	double	*shorter;

	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	hori_check(move, map, hori, player, direction);
	hori[2] = fabs((player[X] - hori[X]) / cos(direction));
	line(MLX_COLOR_WHITESMOKE, img, player[X],player[Y], hori[X],hori[Y]);
	vert_check(move, map, vert, player, direction);
	line(MLX_COLOR_WHITESMOKE, img, player[X],player[Y], vert[X],vert[Y]);
	vert[2] = fabs((player[X] - vert[X]) / cos(direction));
	if (hori[X] < 0 || hori[Y] < 0)
		shorter = vert;
	else if (vert[X] < 0 || vert[Y] < 0)
		shorter = hori;
	else if (hori[2] < vert[2])
		shorter = hori;
	else
		shorter = vert;
	test->distance = shorter[2] * cos(move->direction - direction);
	test->tile_x = shorter[1];
	while (test->tile_x >= 1)
		test->tile_x = test->tile_x - 1;
}

int	get_color(int8_t *start)
{
	int	color;
	int	i;

	i = 0;
	color = 0;
	while (i < 4)
	{
		color = color << 8;
		color = color | *(start + i);
		i++;
	}
	return (color);
}
		// color = color | tex->wall_no->pixels[((int)(((double)i / (double)wall_height) * tex->wall_no->height * tex->wall_no->width) + (int)(tex->wall_no->width * test->tile_x)) * 4 + j];

void	draw_wall(t_array *test, mlx_image_t *img, t_texture *tex)
{
	double	base_distance;
	int		base_height;
	int		skyline;
	int		wall_height;
	int		i;
	int		j = 0;
	int		color = MLX_COLOR_CORAL;
	
	i = 0;
	skyline = img->height / 2;
	base_distance = 1;
	base_height = 200;
	wall_height = base_height / test->distance;


	// uint8_t **twoDimensionalArray = ft_calloc(tex->wall_ea->height * 4, sizeof(uint8_t *));

	// for (int i = 0; i < tex->wall_ea->height * 4; i++) {
	// 	twoDimensionalArray[i] = &tex->wall_ea->pixels[i * tex->wall_ea->width];
	// }
	
	while (i < wall_height)
	{
		
		// need skip for put of window
		if (skyline - wall_height / 2 > 0 && skyline - wall_height / 2 < img->height)
		{
			j = 0;
			color = 0;
			while (j < 4)
			{
				color = color << 8;
				color = color | tex->wall_no->pixels[((int)(((double)i / (double)wall_height) * tex->wall_no->height * tex->wall_no->width) + (int)(tex->wall_no->width * test->tile_x)) * 3 + j];
				j++;
			}
			// printf("%f\n", test->tile_x * 72);
			mlx_put_pixel(img, test->x, skyline - wall_height / 2 + i, color);
		}
		i++;
	}
	// exit (0);
}


#define	DEGREE_TO_RADIAL(degree) ((double)(degree) / 360 * (M_PI * 2))
#define	RADIAL_TO_DEGREE(degree) ((double)(degree) * 360 / (M_PI * 2))

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
{
	uint32_t	i;
	double		pov;
	double		degree_per_pixel;
	double		degree;
	t_array		test;

	pov =  DEGREE_TO_RADIAL(90);
	degree = move->direction - (pov / 2);
	degree_per_pixel = pov / img->width;
	i = 0;
	while(i < img->width)
	{
		test.x = i;
		overshot_protection(&degree);
		sinlgle_ray(&test, move, map, degree, img);
		degree = move->direction - (pov / 2) + degree_per_pixel * i;
		overshot_protection(&degree);
		draw_wall(&test, img, tex);
		i++;
	}
}
