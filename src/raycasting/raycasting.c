/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/15 23:12:10 by lkrabbe          ###   ########.fr       */
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
double	two_point_distants(double *point_a, double *point_b, double rad)
{
	return (fabs((point_a[0] - point_b[0]) / cos(rad)));
}
# define X 0
# define Y 1

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
		while (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X]] != '1')//needs 0 to change with diffrent stuff because sprites and so on
		{
			x_hit[X] += 1;
			x_hit[Y] += -ya;
		}
		return (4);
	}
	else
	{
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
		while (LOGICY && map->elem[(int)y_hit[Y]][(int)y_hit[X]] != '1')
		{
			y_hit[Y] += 1;
			y_hit[X] += -xa;
		}
		return (0);
	}
	else
	{
		while (LOGICY && (map->elem[(int)y_hit[Y] - 1][(int)y_hit[X]] != '1'))
		{
			y_hit[Y] += -1;
			y_hit[X] += xa;
		}
		return (1);
	}
}


void	dda_info_h(t_movement *move, double direction, double *player, t_dda *dda_info)
{
	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
	{
		dda_info->hit[X] = move->x + 1;
		dda_info->offset = 0;
		dda_info->jump = -1 * tan(direction);
		dda_info->dir = 1;
	}
	else
	{
		dda_info->hit[X] = move->x;
		dda_info->offset = -1;
		dda_info->dir = -1;
		dda_info->jump = 1 * tan(direction);
	}
	dda_info->hit[Y] = player[Y] + (player[X] - dda_info->hit[X]) * tan (direction);
}
void	dda_info_v(t_movement *move, double direction, double *player, t_dda *dda_info)
{
	if (direction >= 0 && direction < M_PI)
	{
		dda_info->hit[Y] = move->y + 1;
		dda_info->offset = 0;
		dda_info->jump = -1 / tan(direction);
		dda_info->dir = 1;
	}
	else
	{
		dda_info->hit[Y] = move->y;
		dda_info->offset = -1;
		dda_info->dir = -1;
		dda_info->jump = 1 / tan(direction);
	}
	dda_info->hit[X] = player[X] + (player[Y] - dda_info->hit[Y]) / tan (direction);
}
#define LOGICc dda_info->hit[Y] >= 0 && dda_info->hit[Y] < map->height && dda_info->hit[X] >= 0 && dda_info->hit[X] < map->width
#define LOGICv dda_v->hit[Y] >= 0 && dda_v->hit[Y] < map->height && dda_v->hit[X] >= 0 && dda_v->hit[X] < map->width
#define LOGICh dda_h->hit[Y] >= 0 && dda_h->hit[Y] < map->height && dda_h->hit[X] >= 0 && dda_h->hit[X] < map->width
int	usedda_h(t_dda *dda_info, t_map *map)
{

		while (LOGICc && map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X] + dda_info->offset] == '0')//needs 0 to change with diffrent stuff because sprites and so on
		{
			dda_info->hit[X] += dda_info->dir;
			dda_info->hit[Y] += dda_info->jump;
		}
		if (LOGICc && map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X] + dda_info->offset] != '1' && map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X] + dda_info->offset] != '2' )
			return (-20);
		// if (LOGICc && map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X] + dda_info->offset] != '0')
		// printf("%c ", map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X]+ dda_info->offset]);
		return (1);
}

int	usedda_v(t_dda *dda_info, t_map *map)
{
		while (LOGICc && map->elem[(int)dda_info->hit[Y] + dda_info->offset][(int)dda_info->hit[X]] == '0')
		{
			dda_info->hit[Y] += dda_info->dir;
			dda_info->hit[X] += dda_info->jump;
		}
		if (LOGICc && map->elem[(int)dda_info->hit[Y] + dda_info->offset][(int)dda_info->hit[X]] != '1' && map->elem[(int)dda_info->hit[Y] + dda_info->offset][(int)dda_info->hit[X]] != '2')
			return (-20);
		return (1);
}

void	draw_some_pixel(t_dda *dda_h, t_dda *dda_v, t_map *map, mlx_image_t *img, t_texture *tex, double *player ,t_array *test)
{
	double	base_distance;
	int		base_height;
	int		skyline;
	int		wall_height;
	int		i;
	int		color = MLX_COLOR_CORAL;

	double	*shorter;
	dda_h->hit[2] = two_point_distants(dda_h->hit, player, test->direction);
	dda_v->hit[2] = two_point_distants(dda_v->hit, player, test->direction);
		// printf("here2\n");
	if (dda_h->hit[X] < 0 || dda_h->hit[Y] < 0)
	{
		// printf("herea\n");
		shorter = dda_v->hit;
		test->tile_x = shorter[0];
		test->texture = tex->wall_no;
		color = MLX_COLOR_BLACK;
	}
	else if (dda_v->hit[X] < 0 || dda_v->hit[Y] < 0)
	{
		// printf("hereb\n");
		shorter = dda_h->hit;
		test->tile_x = shorter[1];
		test->texture = tex->wall_we;
		color = MLX_COLOR_RED;
	}
	else if (dda_h->hit[2] < dda_v->hit[2])
	{
		// printf("herec\n");
		shorter = dda_h->hit;
				// printf("herec1\n");
		test->tile_x = shorter[2];
				// printf("herec2\n");
		test->texture = tex->wall_ea;
				// printf("herec3\n");
		color = MLX_COLOR_BLUE;
	}
	else
	{
		// printf("hered\n");
		shorter = dda_v->hit;
		test->tile_x = shorter[0];
		test->texture = tex->wall_so;
		color = MLX_COLOR_GREEN;
	}
	// printf("here\n");
	test->distance = shorter[2];
	while (test->tile_x >= 1)
		test->tile_x = test->tile_x -1.0;
	i = 0;
	skyline = img->height / 2;
	base_distance = 1;
	base_height = 500;
	wall_height = base_height * base_distance/ test->distance;
	while (i  < wall_height)
	{
		if (skyline - wall_height / 2 + i > 0 && skyline - wall_height / 2 + i < img->height)
		{
			color = img_pixel( test->tile_x,((double)i / (double)wall_height), test->texture);
			
			mlx_put_pixel(img, test->x,( skyline - wall_height / 2) + i, color);
		}
		i++;
	}
}


int	usedda_ultra(t_dda *dda_h, t_dda *dda_v, t_map *map, mlx_image_t *img, t_texture *tex, double *player, t_array *test)
{
	int	hit_h;
	int	hit_v;

	hit_h = 0;
	hit_v = 0;
	while(hit_v == 0 || hit_h == 0)
	{
		hit_h = usedda_h(dda_h, map);
		hit_v = usedda_v(dda_v, map);
		if (hit_v < 0 || hit_h < 0)
			draw_some_pixel(dda_h, dda_v, map, img, tex, player, test);
		if (hit_h < 0)
		{
			// printf("h\n");
			hit_h = 0;
			dda_h->hit[X] += dda_h->dir;
			dda_h->hit[Y] += dda_h->jump;
		}
		if (hit_v < 0)
		{
			// printf("v\n");
			hit_v = 0;
			dda_v->hit[Y] += dda_v->dir;
			dda_v->hit[X] += dda_v->jump;
		}
	}
	return (hit_v + hit_h);
}

// int	choose_order(t_dda* dda_v, t_dda* dda_h, double direction, double* player)
// {
// 	dda_h->hit[2] = two_point_distants(dda_h->hit, player, direction);
// 	dda_v->hit[2] = two_point_distants(dda_v->hit, player, direction);
// 	if (dda_h->hit[2] < dda_v->hit[2])
// 		return (0);
// 	return (1);
// }



void	sinlgle_ray(t_array *test, t_movement *move, t_map *map, double direction, mlx_image_t *img, t_texture *tex)
{
	double	player[2];
	double	*shorter;
	int		wall;
	t_dda	dda_h;
	t_dda	dda_v;
	wall = 3;
	int color;
	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	dda_info_h(move, direction, player, &dda_h);
	dda_info_v(move, direction, player, &dda_v);
	wall = usedda_ultra(&dda_h, &dda_v, map, img , tex, player, test);
	// wall = usedda_h(&dda_h, map);
	// wall += usedda_v(&dda_v, map);
	dda_h.hit[2] = two_point_distants(dda_h.hit, player, direction);
	dda_v.hit[2] = two_point_distants(dda_v.hit, player, direction);
	if (dda_h.hit[X] < 0 || dda_h.hit[Y] < 0)
	{
		shorter = dda_v.hit;
		test->tile_x = shorter[0];
		test->texture = tex->wall_no;
		color = MLX_COLOR_BLACK;
	}
	else if (dda_v.hit[X] < 0 || dda_v.hit[Y] < 0)
	{
		shorter = dda_h.hit;
		test->tile_x = shorter[1];
		test->texture = tex->wall_we;
		color = MLX_COLOR_RED;
}
	else if (dda_h.hit[2] < dda_v.hit[2])
	{
		shorter = dda_h.hit;
		test->tile_x = shorter[1];
		test->texture = tex->wall_ea;
		color = MLX_COLOR_BLUE;
	}
	else
	{
		shorter = dda_v.hit;
		test->tile_x = shorter[0];
		test->texture = tex->wall_so;
		color = MLX_COLOR_GREEN;
	}
	test->distance = shorter[2];
	while (test->tile_x >= 1)
		test->tile_x = test->tile_x -1.0;
		//line(color,img,player[X] * img->width / map->width ,player[Y]* img->height / map->height,shorter[X]* img->width / map->width,shorter[Y]* img->width / map->height);
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
	while (i  < wall_height)
	{
		if (skyline - wall_height / 2 + i > 0 && skyline - wall_height / 2 + i < img->height)
		{
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

	fov =  ((double)(60 + move->tmp) / (double)360) * (M_PI * 2);
	degree = move->direction - (fov / 2);
	degree_per_pixel = fov / img->width;
	i = 0;

	while(i < img->width)
	{
		test.direction = degree;
		overshot_protection(&degree);
		test.x = i;
		sinlgle_ray(&test, move, map, degree , img, tex);
		test.distance *= cos(fabs(fov / 2 - i * degree_per_pixel));
		draw_wall(&test, img, tex);
		degree += degree_per_pixel;
		i++;
	}
}
