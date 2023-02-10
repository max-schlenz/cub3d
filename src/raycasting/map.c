
#include	<cub3D.h>

# define WIDTH 1000
# define HEIGHT 1000

# define DEFAULT_ROTATION_SPEED 0.02
# define DEFAULT_DIRECTION 0.00000
# define DEFAULT_VELOCITY 0.01
# define DEFAULT_TOP_DOWN 0.00001


void	default_movement(t_movement *move)
{
	move->x = 1;//?get from parser
	move->y = 1;//?get from parser
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	move->velocity = DEFAULT_VELOCITY;
	move->direction = DEFAULT_DIRECTION; //? will get changed from map input
	move->top_down = DEFAULT_TOP_DOWN;
	move->rotation_speed = DEFAULT_ROTATION_SPEED;
	move->pixel_per_map_tile = 10;
}

void	rendering_loop(void *param)
{
	t_transfer	*transporter;// void pointer
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;// player
	t_map		*map;
	t_texture	*tex;
	t_player	*player;//gone
	t_sprite	*sprite;

	transporter = param;
	mlx = transporter->mlx;
	map = transporter->map;
	img = transporter->img;
	move = transporter->move;
	tex = transporter->tex;
	player = transporter->player;
	sprite = transporter->sprite;
	ft_bzero(img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
	mouse_checker(mlx, move);
	key_checker(mlx, move);
	is_there_something(map, move);
	draw_map(map, img, move, tex, sprite);
	raycasting(mlx, img, move, map, tex);
	// printf("fps: %i\n", (int)(1 / mlx->delta_time));
	update_fps_counter(mlx, img);
}

int	mlx_setup(t_map *map, t_player *player, t_texture *tex, t_sprite *sprite)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	move;
	t_transfer	transporter;// gone
	void	*transpot[20];

	default_movement(&move);
	move.x = player->player_x;
	move.y = player->player_y;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (mlx == NULL)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(mlx, &rendering_loop, &transporter);
	transporter.mlx = mlx;
	transporter.img = img;
	transporter.map = map;
	transporter.move = &move;
	transporter.tex = tex;
	transporter.sprite = sprite;
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main_casting(t_data *data)// input map
{
	mlx_setup(data->map, data->player, data->texture, data->sprite);
	return (0);
}

