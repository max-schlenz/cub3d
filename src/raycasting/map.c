
#include	<cub3D.h>

# define WIDTH 1000
# define HEIGHT 1000

# define DEFAULT_ROTATION_SPEED 0.02
# define DEFAULT_DIRECTION 0.00001
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
}

void	rendering_loop(void *param)
{
	t_transfer	*transporter;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
	t_parse		*map;

	transporter = param;
	mlx = transporter->mlx;
	map = transporter->map;
	img = transporter->img;
	move = transporter->move;
	ft_bzero(img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
	mouse_checker(mlx, move);
	key_checker(mlx, move);
	is_there_something(map, move);
	draw_map(map, img, move);
}

int	mlx_setup(t_parse *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	move;
	t_transfer	transporter;


	default_movement(&move);
	move.x = map->player_x;
	move.y = map->player_y;
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
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main_casting(t_parse *parse)// input map
{
	mlx_setup(parse);
	return (0);
}
