/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/14 15:37:33 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	matrix_two(double *array, double degree)
{
	double	x;
	double	y;

	x = array[0] * cos(degree) - array[1] * sin(degree);
	y = array[0] * sin(degree) + array[1] * cos(degree);
	array[0] = x;
	array[1] = y;
}
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
	int	i;

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

int	hori_check(t_movement *move, t_map *map, double *x_hit, double *player, double direction)
{
	double	ya;

	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
		x_hit[X] = move->x + 1;
	else
		x_hit[X] = move->x;
	x_hit[Y] = player[Y] + (player[X] - x_hit[X]) * tan (direction);
	ya = 1 * tan(direction);
	// from here its the same for hori and vert
	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
	{
			printf("east ");
		while (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X]] != '1')//needs 0 to change with diffrent stuff because sprites and so on
		{
			x_hit[X] += 1;
			x_hit[Y] += -ya;
		}
		return (4);
	}
	else
	{
			printf("west ");
		while (LOGICX && (map->elem[(int)x_hit[Y]][(int)x_hit[X] - 1] != '1'))
		{
			x_hit[X] += -1;
			x_hit[Y] += ya;
		}
		return(2);
	}
}

int	vert_check(t_movement *move, t_map *map, double *y_hit, double *player, double direction)
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
			printf("south ");
		while (LOGICY && map->elem[(int)y_hit[Y]][(int)y_hit[X]] != '1')
		{
			y_hit[Y] += 1;
			y_hit[X] += -xa;
		}
		return (0);
	}
	else
	{
			printf("north ");
		while (LOGICY && (map->elem[(int)y_hit[Y] - 1][(int)y_hit[X]] != '1'))
		{
			y_hit[Y] += -1;
			y_hit[X] += xa;
		}
		return (1);
	}
}

void	sinlgle_ray(t_array *test, t_movement *move, t_map *map, double direction, mlx_image_t *img, t_texture *tex)
{
	double	hori[3];
	double	vert[3];
	double	player[2];
	double	*shorter;
	int		wall;

	// direction = direction / 1.000;
//if(side == 0) perpWallDist = (sideDistX - deltaDistX);
	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	wall = hori_check(move, map, hori, player, direction);
	hori[2] = fabs((player[X] - hori[X]) / cos(direction)) ;
	wall += vert_check(move, map, vert, player, direction);
	vert[2] = fabs((player[X] - vert[X]) / cos(direction)) ;
	// vert[2] = sqrt((player[X] - vert[X]) * (player[X] - vert[X]) + (player[Y] - vert[Y]) * (player[Y] - vert[Y]));
	// hori[2] = sqrt((player[X] - hori[X]) * (player[X] - hori[X]) + (player[Y] - hori[Y]) * (player[Y] - hori[Y]));
	if (hori[X] < 0 || hori[Y] < 0)
	{
		shorter = vert;
		test->tile_x = shorter[0];
		printf("vert ");
		if (wall & 1)
			test->texture = tex->wall_no;
		else
			test->texture = tex->wall_so;
	}
	else if (vert[X] < 0 || vert[Y] < 0)
	{
		shorter = hori;
		test->tile_x = shorter[1];
			printf("hori ");
		if (wall & 2)
			test->texture = tex->wall_ea;
		else
			test->texture = tex->wall_we;
	}
	else if (hori[2] < vert[2])
	{
		shorter = hori;
		test->tile_x = shorter[1];
		printf("hori");
		if (wall & 2)
			test->texture = tex->wall_ea;
		else
			test->texture = tex->wall_we;
	}
	else
	{
		shorter = vert;
		test->tile_x = shorter[0];
			printf("vert ");
		if (wall & 1)
			test->texture = tex->wall_no;
		else
			test->texture = tex->wall_so;
	}
	printf("x%f y%f\n",shorter[X],shorter[Y]);
	// printf("before%f\n",shorter[2]);
	// printf("dif %f - %f  = %f\n",move->direction , direction,move->direction - direction);
	test->distance = shorter[2];
	while (test->tile_x >= 1)
		test->tile_x = test->tile_x -1.0;
	// line(MLX_COLOR_AQUA,img,player[X] * img->width / map->width ,player[Y]* img->height / map->height,shorter[X]* img->width / map->width,shorter[Y]* img->width / map->height);
	// printf("after%f\n\n",test->distance);
	// matrix_two(shorter,move->direction - direction);
	// test->distance = fabs((player[X] - vert[X]));
}

int	get_color(uint8_t *start)
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



int	img_pixel(double x_p, double y_p, mlx_texture_t *tex)
{
	uint8_t *ptr;
	int	x;
	int	y;

	x = (int)(x_p * tex->width);
	y =(int)(y_p * tex->height) * (tex->width);
	ptr = &tex->pixels[(int)(x * 4 + y * 4)];
	return (get_color(ptr));
}

void	draw_wall(t_array *test, mlx_image_t *img, t_texture *tex)
{
	double	base_distance;
	int		base_height;
	int		skyline;
	int		wall_height;
	int		i;
	int		color = MLX_COLOR_CORAL;
	
	i = 0;
	skyline = img->height / 2;
	base_distance = 1;
	base_height = 500;
	wall_height = base_height * base_distance/ test->distance;
	// test->texture = tex->wall_no;
	while (i  < wall_height)
	{
		// need skip for put of window
		if (skyline - wall_height / 2 + i > 0 && skyline - wall_height / 2 + i < img->height)
		{
			//get_pixel_for_sprites
			color = img_pixel( test->tile_x,((double)i / (double)wall_height), test->texture);
			mlx_put_pixel(img, test->x,( skyline - wall_height / 2) + i, color);
		}
		i++;
	}
}


#define	DEGREE_TO_RADIAL(degree) ((double)(degree) / 360 * (M_PI * 2))
#define	RADIAL_TO_DEGREE(degree) ((double)(degree) * 360 / (M_PI * 2))

void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
{
	int		i;
	double	fov;
	double	degree_per_pixel;
	double	degree;
	t_array	test;

	fov =  ((double)(90 + move->tmp) / (double)360) * (M_PI * 2);
	degree = move->direction - (fov / 2);
	degree_per_pixel = fov / img->width;
	i = 0;
	// printf("%d\n",move->tmp);

	// printf(">>%f player %f\n",degree ,move->direction);
	while(i < img->width)
	{
		test.direction = degree;
		overshot_protection(&degree);
		test.x = i;
		printf("move x %d move y %d tile x %f tile y %f\n",move->x ,move->y, move->tile_x, move->tile_y);
		printf("degree %f degree %f\n",RADIAL_TO_DEGREE(move->direction) ,RADIAL_TO_DEGREE(degree));
		sinlgle_ray(&test, move, map, degree , img, tex);
		// test.distance *= cos(fabs(fov / 2 - i * degree_per_pixel));
		printf("%f \n",test.distance);
		draw_wall(&test, img, tex);
		degree += degree_per_pixel;
		i++;
	}
	printf("-----\n");
	// printf(">>%f %i\n",degree,i);
	// exit (0);
}
