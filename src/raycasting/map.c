
#include	<cub3D.h>

# define WIDTH 1000
# define HEIGHT 1000
# define X 0
# define Y 1
# define DEFAULT_ROTATION_SPEED 0.02
# define DEFAULT_DIRECTION 0.00001
# define DEFAULT_VELOCITY 0.01
# define DEFAULT_TOP_DOWN 0.00001 //? maybe not use in the end
# define PI_TIMES_TWO 6.28318530718

typedef struct s_movement{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
	double	direction;
	double	top_down;
	double	velocity;//? settig value
	double	rotation_speed;//? settig value
}t_movement;

typedef struct s_transfer{
	t_parse		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
}t_transfer;

typedef struct s_array // for each pixel ont the horizontal  >> t_array array[img->width] //need to  care about  rezising free and alloc
{
	int				x;
	double			tile_x;
	double			direction;
	double			distance;
	mlx_texture_t	*texture;
}t_array;

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

int	wall_check(t_parse *map, t_movement *move, int f_b, int l_r)
{
	if (map->array[move->y + f_b][move->x + l_r] == '1')
		return (1);
	return (0);
}

void	check_west(t_parse	*map, t_movement *move)
{
	if (move->tile_x < 0)
	{
		if (wall_check(map, move, 0, -1) == 0)
		{
			move->x--;
			move->tile_x = 1;
		}
		else
		{
			printf("west\n");
			move->tile_x = 0.01;
		}
	}
}

void	check_east(t_parse	*map, t_movement *move)
{
	if (move->tile_x > 1)
	{
		if (wall_check(map, move, 0, +1) == 0)
		{
			move->x++;
			move->tile_x = 0;
		}
		else
		{
			printf("east\n");
			move->tile_x = 0.99;
		}
	}
}

void	check_north(t_parse	*map, t_movement *move)
{
	if (move->tile_y < 0)
	{
		if (wall_check(map, move, -1, 0) == 0)
		{
			move->y--;
			move->tile_y = 1;
		}
		else
		{
			printf("north\n");
			move->tile_y = 0.01;
		}
	}
}

void	check_south(t_parse	*map, t_movement *move)
{
	if (move->tile_y > 1)
	{
		if (wall_check(map, move, +1, 0) == 0)
		{
			move->y++;
			move->tile_y = 0;
		}
		else
		{
			printf("south\n");
			move->tile_y = 0.99;
		}
	}
}

void	is_there_something(t_parse *map, t_movement *move)
{
	check_north(map, move);
	check_south(map, move);
	check_east(map, move);
	check_west(map, move);
}
/**
 * @brief 
 * 
 * x' = xcosθ - ysinθ.
 * y' = xsinθ + ycosθ.
 * 
 */
void	matrix_movement(t_movement *move, double *array)
{
	double	x;
	double	y;

	x = array[X] * cos(move->direction) - array[Y] * sin(move->direction);
	y = array[X] * sin(move->direction) + array[Y] * cos(move->direction);
	if (array[X] || array[Y])
	printf("X %f ==> %f\nY %f ==> %f\n", array[X], x, array[Y], y);
}

/**
 * @brief change position based data depending on specific key pressed.
 * also close window for [esc]
 * 
 *! @todo movement needs to care about current direction aka x * cos() and  y * cos()
 * 
 */
void	key_checker(mlx_t *mlx, t_movement *move)
{
	double	movement[2];

	movement[X] = 0;
	movement[Y] = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		movement[Y] -= move->velocity;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		movement[X] -= move->velocity;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		movement[Y] += move->velocity;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		movement[X] += move->velocity;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Q))
	{
		move->direction += 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_E))
	{
		move->direction -= 0.1;
	}
	matrix_movement(move, movement);
	move->tile_x += movement[X];
	move->tile_y += movement[Y];
}

void	mouse_checker(mlx_t *mlx, t_movement *move)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if ((WIDTH / 2 - x) < 0)
	{
		move->direction += move->rotation_speed;// coud be based on a factor so it rotates faster
	}
	else if ((WIDTH / 2 - x) > 0)
	{
		move->direction -= move->rotation_speed;
	}
	if ((HEIGHT / 2 - y) < 0)//? maybe not used in the end// top down for  tranlate the casting line up or down
	{
		move->top_down += move->rotation_speed;
	}
	else if ((HEIGHT / 2 - y) > 0)//? maybe not used in the end
	{
		move->top_down -= move->rotation_speed;
	}
	while (move->direction > PI_TIMES_TWO)
		move->direction -= PI_TIMES_TWO;
	while (move->direction < 0)
		move->direction += PI_TIMES_TWO;
	while (move->top_down > PI_TIMES_TWO)
		move->top_down -= PI_TIMES_TWO;
	while (move->top_down < 0)
		move->top_down += PI_TIMES_TWO;
	mlx_set_mouse_pos(mlx, WIDTH / 2, HEIGHT / 2);
}

void	draw_player_char(mlx_image_t *img, int y, int x)
{
	mlx_put_pixel(img, x, y, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x + 1, y, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x, y + 1, MLX_COLOR_BLACK);
	mlx_put_pixel(img, x + 1, y + 1, MLX_COLOR_BLACK);
}




void	cast_array(mlx_image_t *img, t_movement *move, t_parse *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;




	mlx_put_pixel(img, x, y, MLX_COLOR_AQUA);
}

void	draw_player_on_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	int	x;
	int	y;

	x = move->x * (WIDTH / map->map_width);
	y = move->y * (HEIGHT / (map->map_height));
	x += move->tile_x * (WIDTH / (map->map_width));
	y += move->tile_y * (HEIGHT / map->map_height);
	draw_player_char(img, y, x);
	cast_array(img, move, map);
}

# define pixel_per_y (int)(y /((double)HEIGHT / (map->map_height)))
# define pixel_per_x (int)(x /((double)WIDTH / map->map_width))
void	draw_map(t_parse *map, mlx_image_t *img, t_movement *move)
{
	double	x;
	double	y;


	x = 0;
	y = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			//printf("DRAW: %i y/ppy = %i x/ppx = %i\n",y ,pixel_per_y, pixel_per_x);
			if (map->array[pixel_per_y][pixel_per_x] == '1')// 999 / 111 = 9
				mlx_put_pixel(img, x, y, MLX_COLOR_ORANGERED);
			else if (map->array[pixel_per_y][pixel_per_x] == '0')
				mlx_put_pixel(img, x, y, MLX_COLOR_DARKSALMON);
			else if (map->array[pixel_per_y][pixel_per_x] == '2')
				mlx_put_pixel(img, x, y, MLX_COLOR_BLUE);
			else
				mlx_put_pixel(img, x, y, MLX_COLOR_WHITE);
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
	ft_memset(img->pixels, MLX_COLOR_BURLYWOOD,(WIDTH * HEIGHT * sizeof(u_int32_t)));
	//ft_bzero(img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
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
