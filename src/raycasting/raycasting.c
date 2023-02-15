/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/15 18:50:11 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

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

int	north_dda(double* x_hit, double jump,t_map* map)
{
		if (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X]] != '1')
		{
			x_hit[X] += 1;
			x_hit[Y] += -jump;
		}
		else
			return (4);
		return (0);
}

int	south_dda(double* x_hit, double jump,t_map* map)
{
		if (LOGICX && map->elem[(int)x_hit[Y]][(int)x_hit[X] - 1] != '1')
		{
			x_hit[X] += -1;
			x_hit[Y] += jump;
		}
		else
			return(2);
		return (0);
}

// int	west_dda(double* x_hit, double jump,t_map* map)
// {

// }

// int	east_dda(double* x_hit, double jump,t_map* map)
// {

// }

typedef struct s_dda
{
	double	jump;
	int		(*f_ptr)(double* hit, double jump,t_map* map);
	double*	hit;
	// double	jump_y;
	// int		(*f_ptr_y)(double* , double ,t_map* );
}t_dda;


void	north_or_south(t_dda *dda_info, t_movement *move, double *player, double direction)
{
	if (direction >= M_PI_2 && direction < M_PI + M_PI_2)
	{
		dda_info->hit[X] = move->x + 1;
		dda_info->f_ptr = &north_dda;
	}
	else
	{
		dda_info->f_ptr = &south_dda;
		dda_info->hit[X] = move->x;
	}
	dda_info->hit[Y] = player[Y] + (player[X] - dda_info->hit[X]) * tan (direction);
	dda_info->jump = 1 * tan(direction);
}

int	hori_check( t_dda *dda_info, t_map *map)
{
	int	d;

	d = 0;
	while(d == 0)
	{
		d = dda_info->f_ptr(dda_info->hit, dda_info->jump, map);
	}
	return (d);
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

/**
 * @brief give you the distants between 2 points
 * 
 *
 */
double	two_point_distants(double *point_a, double *point_b, double rad)
{
	return (fabs((point_a[0] - point_b[0]) / cos(rad)));
}
	
void	sinlgle_ray(t_array *test, t_movement *move, t_map *map, double direction, mlx_image_t *img, t_texture *tex)
{
	double	hori[3];
	double	vert[3];
	double	player[2];
	double	*shorter;
	int		wall;
	t_dda	dda_info;

	dda_info.f_ptr = NULL;
	printf("%p\n",&north_dda);
	printf("%p\n",&south_dda);
	printf("%p\n",dda_info.f_ptr);
	north_or_south(&dda_info, move, player, direction);
	printf("%p\n",dda_info.f_ptr);
	player[X] = move->x + move->tile_x;
	player[Y] = move->y + move->tile_y;
	wall = hori_check(&dda_info, map);//for tex
	wall += vert_check(move, map, vert, player, direction);//for tex
	hori[2] = two_point_distants(hori, player, direction);
	vert[2] = two_point_distants(vert, player, direction);
	if (hori[X] < 0 || hori[Y] < 0)
	{
		shorter = vert;
		test->tile_x = shorter[0];
		if (wall & 1)
			test->texture = tex->wall_no;
		else
			test->texture = tex->wall_so;
	}
	else if (vert[X] < 0 || vert[Y] < 0)
	{
		shorter = hori;
		test->tile_x = shorter[1];
		if (wall & 2)
			test->texture = tex->wall_ea;
		else
			test->texture = tex->wall_we;
	}
	else if (hori[2] < vert[2])
	{
		shorter = hori;
		test->tile_x = shorter[1];
		if (wall & 2)
			test->texture = tex->wall_ea;
		else
			test->texture = tex->wall_we;
	}
	else
	{
		shorter = vert;
		test->tile_x = shorter[0];
		if (wall & 1)
			test->texture = tex->wall_no;
		else
			test->texture = tex->wall_so;
	}
	test->distance = shorter[2];
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

void	draw_wall(t_array *test, mlx_image_t *img, t_texture *tex,double fov)
{
	double	base_distance;
	double		base_height;
	double		skyline;
	double		wall_height;
	double		i;
	double		color = MLX_COLOR_CORAL;
	
	i = 0;
	skyline = img->height / 2;
	base_distance = (img->width / 2) * tan(fov/2);
	base_height = 100;
	wall_height = 1/ test->distance * base_distance;
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

	fov =  ((double)(60) / (double)360) * (M_PI * 2);
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
		draw_wall(&test, img, tex,fov);
		degree += degree_per_pixel;
		i++;
	}
	// exit (0);
}
