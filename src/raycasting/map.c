
#include	<cub3D.h>

# define WIDTH 1000
# define HEIGHT 1000
# define X 0
# define Y 1


typedef struct s_movement{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
	double	velocity;
	double	direction;
}t_movement;

typedef struct s_transfer{
	t_parse		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
}t_transfer;



void	default_movement(t_movement *move)
{
	move->x = 1;//?get from parser
	move->y = 1;//?get from parser
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	move->velocity = 0.01;
	move->direction = 0; //? will get changed from map input
}

int	wall_check(t_parse *map, t_movement *move, int f_b, int l_r)
{
	if (map->array[move->y + f_b][move->x + l_r]== '1')
		return (1);
	return (0);
}

void	check_west(t_parse	*map, t_movement *move)
{
	if (move->tile_x < 0)
	{
		if (wall_check(map, move, 0, -1) == 0)
		{
			printf("west\n");
			move->x--;
			move->tile_x = 1;
		}
		else
			move->tile_x = 0.10;
	}
}

void	check_east(t_parse	*map, t_movement *move)
{
	if (move->tile_x > 1)
	{
		if (wall_check(map, move, 0, +1) == 0)
		{
			printf("east\n");		
			move->x++;
			move->tile_x = 0;
		}
		else
			move->tile_x = 0.90;
	}
}

void	check_south(t_parse	*map, t_movement *move)
{
	if (move->tile_y < 0)
	{
		if (wall_check(map, move, -1, 0) == 0)
		{
			printf("south\n");
			move->y--;
			move->tile_y = 1;
		}
		else
			move->tile_y = 0.1;
	}
}

void	check_north(t_parse	*map, t_movement *move)
{
	if (move->tile_y > 1)
	{
		if (wall_check(map, move, +1, 0) == 0)
		{
			printf("north\n");
			move->y++;
			move->tile_y = 0;
		}
		else
			move->tile_y = 0.1;
	}
}

void	is_there_something(t_parse *map, t_movement *move)
{
	check_north(map, move);
	check_south(map, move);
	check_east(map, move);
	check_west(map, move);
}

void	key_checker(mlx_t *mlx, t_movement *move)
{
	double	movement[2];

	movement[X] = 0;
	movement[Y] = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		movement[Y] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		movement[X] -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		movement[Y] += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		movement[X] += move->velocity;
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
	// printf("tile  %f %f\n", move->tile_y, move->tile_x);
	// printf("player %i %i\n", move->y, move->x);
}

void	mouse_checker(mlx_t *mlx, t_movement *move)
{
	//int	movement[2];
	int	x;
	int	y;
	mlx_get_mouse_pos(mlx, &x, &y);
	// printf("mouse x = %i, y = %i\n", x, y);
}
	
void	draw_player_on_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	int	x;
	int	y;

	// printf("per pixle %i == %i\n",(HEIGHT / (map->map_height)), (WIDTH / map->map_width));
	// printf("start pos %i == %i\n",(move->x), (move->y));
	// printf("tile %f == %f\n", (move->tile_x), move->tile_y);
	x = move->x * (WIDTH / map->map_width);
	y = move->y * (HEIGHT / (map->map_height));
	//printf("x = %i and y %i\n", x, y);
	x += move->tile_x * (WIDTH / (map->map_width));
	y += move->tile_y * (HEIGHT / map->map_height);
	// printf("x = %i and y %i\n", x, y);
	mlx_put_pixel(img, x, y, MLX_COLOR_Black);
	mlx_put_pixel(img, x + 1, y, MLX_COLOR_Black);
	mlx_put_pixel(img, x, y + 1, MLX_COLOR_Black);
	mlx_put_pixel(img, x + 1, y + 1, MLX_COLOR_Black);
}

void	draw_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	int	x;
	int	y;
	int	pixel_per_y;
	int	pixel_per_x;

	x = 0;
	y = 0;
	pixel_per_y = (HEIGHT / (map->map_height));
	pixel_per_x = (WIDTH / map->map_width);
	while (y < img->height)
	{
		while (x < img->width)
		{
			if (map->array[y / pixel_per_y][x / pixel_per_x] == '1')
				mlx_put_pixel(img, x, y, MLX_COLOR_OrangeRed);
			else if (map->array[y / pixel_per_y][x / pixel_per_x] == '0')
				mlx_put_pixel(img, x, y, MLX_COLOR_DarkSalmon);
			else
				mlx_put_pixel(img, x, y, MLX_COLOR_Blue);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player_on_map(map, img, move);
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
	// printf("x = %i and y %i\n", img->height, img->width);
	draw_map(map, img, move);
	// mlx_put_string(mlx, "hello",150,150);
}

int	mlx_setup(t_parse *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	move;
	t_transfer	transporter;

	default_movement(&move);
	mlx = mlx_init(WIDTH, HEIGHT, "map", 1);
	if (mlx == NULL)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
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
	parse->map_height += -1;
	mlx_setup(parse);
	return (0);
}
