/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 07:58:02 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/20 12:16:50 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

void	default_movement(t_movement *move, mlx_image_t *img_bg, \
mlx_image_t *img, t_player *player)
{
	move->x = player->player_x;
	move->y = player->player_y;
	if (player->player_dir == 'N')
		move->direction = M_PI_2 + M_PI;
	else if (player->player_dir == 'E')
		move->direction = M_PI;
	else if (player->player_dir == 'S')
		move->direction = M_PI_2;
	else if (player->player_dir == 'W')
		move->direction = 0;
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	move->velocity = DEFAULT_VELOCITY;
	move->top_down = img->height;
	move->rotation_speed = DEFAULT_ROTATION_SPEED;
}

void	rendering_loop(void *param)
{
	t_transfer	*t;

	t = param;
	ft_bzero(t->img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
	mouse_checker(t->mlx, t->move, t->img_bg);
	key_checker(t->mlx, t->move, t->map);
	is_there_something(t->map, t->move);
	raycasting(t->img, t->move, t->map, t->tex);
	draw_map(t->map, t->img, t->move, t->tex, t->sprites);
	update_fps_counter(t->mlx, t->img);
}

int	mlx_setup(t_data *data, t_map *map, t_player *player, \
t_texture *tex, t_sprites *sprites)
{
	t_movement	move;
	t_transfer	t;

	move.x = player->player_x;
	move.y = player->player_y;
	t.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (t.mlx == NULL)
		cleanup(data);
	t.img_bg = create_bg_layer(t.mlx, map->color_ceiling, \
	map->color_floor);
	t.img = mlx_new_image(t.mlx, WIDTH, HEIGHT);
	t.img_map = mlx_new_image(t.mlx, WIDTH, HEIGHT);
	t.sprites = sprites;
	default_movement(&move, t.img_bg, t.img, player);
	mlx_set_cursor_mode(t.mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(t.mlx, t.img_bg, 0, 0);
	mlx_image_to_window(t.mlx, t.img, 0, 0);
	mlx_image_to_window(t.mlx, t.img_map, 0, 0);
	mlx_loop_hook(t.mlx, &rendering_loop, &t);
	t.map = map;
	t.move = &move;
	t.tex = tex;
	mlx_loop(t.mlx);
	mlx_terminate(t.mlx);
	return (0);
}

int	main_casting(t_data *data)
{
	mlx_setup(data, data->map, data->player, data->texture, data->sprites);
	return (0);
}
