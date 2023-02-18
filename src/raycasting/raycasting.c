/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/18 07:42:40 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

double	two_point_distants(double *point_a, double *point_b, double rad)
{
	return (fabs((point_a[0] - point_b[0]) / cos(rad)));
}

void	use_vert(t_dda *dda_v, t_array *ray, t_map *map, t_texture *tex)
{
	ray->point = dda_v->hit;
	ray->tile_x = ray->point[0];
	if (map->elem[(int)dda_v->hit[Y] + dda_v->offset] \
	[(int)dda_v->hit[X]] == 'd')
		ray->texture = tex->open_door;
	else if (map->elem[(int)dda_v->hit[Y] + dda_v->offset] \
	[(int)dda_v->hit[X]] == 'D')
		ray->texture = tex->closed_door;
	else if (dda_v->dir == -1)
		ray->texture = tex->wall_no;
	else
		ray->texture = tex->wall_so;
}

void	use_hori(t_dda *dda_h, t_array *ray, t_map *map, t_texture *tex)
{
	ray->point = dda_h->hit;
	ray->tile_x = ray->point[1];
	if (map->elem[(int)dda_h->hit[Y]] \
	[(int)dda_h->hit[X] + dda_h->offset] == 'd')
		ray->texture = tex->open_door;
	else if (map->elem[(int)dda_h->hit[Y]] \
	[(int)dda_h->hit[X] + dda_h->offset] == 'D')
		ray->texture = tex->closed_door;
	else if (dda_h->dir == -1)
		ray->texture = tex->wall_we;
	else
		ray->texture = tex->wall_ea;
}

void	sinlgle_ray(t_array *ray, t_map *map, \
mlx_image_t *img, t_texture *tex)
{
	t_dda	dda_h;
	t_dda	dda_v;

	dda_info_h(ray->player_x, ray->direction, ray->player, &dda_h);
	dda_info_v(ray->player_y, ray->direction, ray->player, &dda_v);
	usedda_ultra(&dda_h, &dda_v, map);
	dda_h.hit[2] = two_point_distants(dda_h.hit, ray->player, ray->direction);
	dda_v.hit[2] = two_point_distants(dda_v.hit, ray->player, ray->direction);
	if (dda_h.hit[X] < 0 || dda_h.hit[Y] < 0)
		use_vert(&dda_v, ray, map, tex);
	else if (dda_v.hit[X] < 0 || dda_v.hit[Y] < 0)
		use_hori(&dda_h, ray, map, tex);
	else if (dda_h.hit[2] < dda_v.hit[2])
		use_hori(&dda_h, ray, map, tex);
	else
		use_vert(&dda_v, ray, map, tex);
	ray->distance = ray->point[2];
	while (ray->tile_x >= 1)
		ray->tile_x = ray->tile_x -1.0;
}

void	raycasting(mlx_image_t *img, t_movement *move, \
t_map *map, t_texture *tex)
{
	int		i;
	double	fov;
	double	degree_per_pixel;
	double	degree;
	t_array	ray;

	ray.player_x = move->x;
	ray.player_y = move->y;
	ray.player[X] = move->x + move->tile_x;
	ray.player[Y] = move->y + move->tile_y;
	fov = ((double)(60 + move->tmp) / (double)360) * (M_PI * 2);
	degree = move->direction - (fov / 2);
	degree_per_pixel = fov / img->width;
	i = 0;
	while (i < img->width)
	{
		ray.direction = degree;
		overshot_protection(&degree);
		ray.x = i;
		sinlgle_ray(&ray, map, img, tex);
		ray.distance *= cos(fabs(fov / 2 - i * degree_per_pixel));
		draw_wall(&ray, img, tex, fov);
		degree += degree_per_pixel;
		i++;
	}
}
