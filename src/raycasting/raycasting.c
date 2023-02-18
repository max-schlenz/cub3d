/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 00:49:46 by lkrabbe          ###   ########.fr       */
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

int	usedda_h(t_dda *dda_info, t_map *map)
{

		while (LOGICc && map->elem[(int)dda_info->hit[Y]][(int)dda_info->hit[X] + dda_info->offset] == '0')//needs 0 to change with diffrent stuff because sprites and so on
		{
			dda_info->hit[X] += dda_info->dir;
			dda_info->hit[Y] += dda_info->jump;
		}
		return (1);
}

int	usedda_v(t_dda *dda_info, t_map *map)
{
		while (LOGICc && map->elem[(int)dda_info->hit[Y] + dda_info->offset][(int)dda_info->hit[X]] == '0')
		{
			dda_info->hit[Y] += dda_info->dir;
			dda_info->hit[X] += dda_info->jump;
		}
		return (1);
}

int	usedda_ultra(t_dda *dda_h, t_dda *dda_v, t_map *map)
{
	int	hit_h;
	int	hit_v;

	hit_h = 0;
	hit_v = 0;
	while(hit_v == 0 || hit_h == 0)
	{
		hit_h = usedda_h(dda_h, map);
		hit_v = usedda_v(dda_v, map);
		if (hit_h < 0)
		{
			hit_h = 0;
			dda_h->hit[X] += dda_h->dir;
			dda_h->hit[Y] += dda_h->jump;
		}
		if (hit_v < 0)
		{
			hit_v = 0;
			dda_v->hit[Y] += dda_v->dir;
			dda_v->hit[X] += dda_v->jump;
		}
	}
	return (hit_v + hit_h);
}

void	use_vert(t_dda *dda_v, t_array *test, t_map *map , t_texture *tex)
{
	test->point = dda_v->hit;
	test->tile_x = test->point[0];
	if (map->elem[(int)dda_v->hit[Y] + dda_v->offset][(int)dda_v->hit[X]] == 'd')
		test->texture = tex->open_door;
	else if (map->elem[(int)dda_v->hit[Y] + dda_v->offset][(int)dda_v->hit[X]] == 'D')
		test->texture = tex->closed_door;
	else if (dda_v->dir == -1)
		test->texture = tex->wall_no;
	else
		test->texture = tex->wall_so;
}

void	use_hori(t_dda *dda_h, t_array *test, t_map *map , t_texture *tex)
{
	test->point = dda_h->hit;
	test->tile_x = test->point[1];
	if (map->elem[(int)dda_h->hit[Y]][(int)dda_h->hit[X ] + dda_h->offset] == 'd')
		test->texture = tex->open_door;
	else if (map->elem[(int)dda_h->hit[Y]][(int)dda_h->hit[X ] + dda_h->offset] == 'D')
		test->texture = tex->closed_door;
	else if (dda_h->dir == -1)
		test->texture = tex->wall_we;
	else
		test->texture = tex->wall_ea;
}

void	sinlgle_ray(t_array *test, t_movement *move, t_map *map, double direction, mlx_image_t *img, t_texture *tex)
{
	double	player[2];
	t_dda	dda_h;
	t_dda	dda_v;

	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	dda_info_h(move, direction, player, &dda_h);
	dda_info_v(move, direction, player, &dda_v);
	usedda_ultra(&dda_h, &dda_v, map);
	dda_h.hit[2] = two_point_distants(dda_h.hit, player, direction);
	dda_v.hit[2] = two_point_distants(dda_v.hit, player, direction);
	if (dda_h.hit[X] < 0 || dda_h.hit[Y] < 0)
		use_vert(&dda_v, test, map , tex);
	else if (dda_v.hit[X] < 0 || dda_v.hit[Y] < 0)
		use_hori(&dda_h, test, map , tex);
	else if (dda_h.hit[2] < dda_v.hit[2])
		use_hori(&dda_h, test, map , tex);
	else
		use_vert(&dda_v, test, map , tex);
	test->distance = test->point[2];
	while (test->tile_x >= 1)
		test->tile_x = test->tile_x -1.0;
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

void	draw_wall(t_array *test, mlx_image_t *img, t_texture *tex,double fov, int fact)
{
	int		skyline;
	int		wall_height;
	int		i;
	int		color;
	
	i = 0;
	skyline = img->height / 2;
	wall_height = 3.2 / test->distance * (img->width / 2) * tan(fov/2);
	while (i  < wall_height)
	{
		if (skyline - wall_height / 2 + i < 0)
			i = wall_height / 2 - skyline;
		if(skyline - wall_height / 2 + i > img->height)
			break;
		if (skyline - wall_height / 2 + i > 0 && skyline - wall_height / 2 + i < img->height)
		{
			color = img_pixel( test->tile_x,((double)i / (double)wall_height), test->texture);
			mlx_put_pixel(img, test->x,(skyline - wall_height / 2) + i, color);
		}
		i++;
	}
}

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
		draw_wall(&test, img, tex,fov, move->tmp);
		degree += degree_per_pixel;
		i++;
	}
}
