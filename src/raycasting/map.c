
#include	<cub3D.h>


# define DEFAULT_ROTATION_SPEED 0.22
# define DEFAULT_DIRECTION 0.174533
# define DEFAULT_VELOCITY 0.05


void	default_movement(t_movement *move, mlx_image_t *img_bg, mlx_image_t *img, t_player *player)
{
	move->x = player->player_x;//?get from parser
	move->y = player->player_y;//?get from parser
	// move->direction = 30;/
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	move->velocity = DEFAULT_VELOCITY;
	move->direction = DEFAULT_DIRECTION; //? will get changed from map input
	move->top_down = img->height;
	move->rotation_speed = DEFAULT_ROTATION_SPEED;
	move->pixel_per_map_tile = 10;
	move->tmp = 0;
}

void	move_bg(t_map *map, mlx_image_t *img_bg, t_movement *move, t_texture *tex, t_sprite *sprite)
{
	// img_bg->instances[0].y = move->top_down;
	printf("%i\n", img_bg->instances[0].y);
}

void	rendering_loop(void *param)
{
	t_transfer	*transporter;// void pointer
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_bg;
	t_movement	*move;// player
	t_map		*map;
	t_texture	*tex;
	t_player	*player;//gone
	t_sprite	*sprite;

	transporter = param;
	mlx = transporter->mlx;
	map = transporter->map;
	img = transporter->img;
	img_bg = transporter->img_bg;
	move = transporter->move;
	tex = transporter->tex;
	player = transporter->player;
	sprite = transporter->sprite;
	ft_bzero(img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
	mouse_checker(mlx, move, img_bg);
	key_checker(mlx, move, map);
	is_there_something(map, move);

	// draw_map(map, img, move, tex, sprite);
	raycasting(mlx, img, move, map, tex);
	// printf("fps: %i\n", (int)(1 / mlx->delta_time));
	update_fps_counter(mlx, img);
}

int	mlx_setup(t_data *data, t_map *map, t_player *player, t_texture *tex, t_sprite *sprite)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_bg;
	t_movement	move;
	t_transfer	transporter;// gone
	void	*transpot[20];

	move.x = player->player_x;
	move.y = player->player_y;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (mlx == NULL)
		cleanup(data);
	img_bg = create_background_layer(mlx, map->color_ceiling, map->color_floor);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	default_movement(&move, img_bg, img, player);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(mlx, img_bg, 0, 0);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &rendering_loop, &transporter);
	transporter.mlx = mlx;
	transporter.img = img;
	transporter.img_bg = img_bg;
	transporter.map = map;
	transporter.move = &move;
	transporter.tex = tex;
	transporter.sprite = sprite;
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

int	main_casting(t_data *data)// input map
{
	mlx_setup(data, data->map, data->player, data->texture, data->sprite);
	return (0);
}
