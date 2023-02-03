
#include	<cub3D.h>

# define WIDTH 2000 
# define HEIGHT 2000 
# define X 0
# define Y 1


typedef struct s_map{
	char	**map;
}t_map;

typedef struct s_movement{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
	double	velocity;
	double	direction;
}t_movement;

typedef struct s_transfer{
	int			*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
}t_transfer;



void	default_movement(t_movement *move)
{
	move->x = 100;//?get from parser
	move->y = 100;//?get from parser
	move->tile_x = 0.5;
	move->tile_y = 0.5;
	move->velocity = 100;
	move->direction = 0; //? will get changed from map input
}

void	key_checker(mlx_t *mlx, t_movement *move)
{

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move->y += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move->x += move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move->y -= move->velocity;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move->x -= move->velocity;
	//if (move->tile_x < 0 )	//! check valid movement here
	// {
	// 	move->x--;
	// 	move->tile_x = 0;
	// 	//printf("change x");
	// }
	// if (move->tile_x > 0 )	//! check valid movement here
	// {
	// 	move->x++;
	// 	move->tile_x = 1;
	// }
	// if (move->tile_y < 0 )	//! check valid movement here
	// {
	// 	move->y--;
	// 	move->tile_y = 0;
	// }
	// if (move->tile_y > 0 )	//! check valid movement here
	// {
	// 	move->y++;
	// 	move->tile_y = 1;
	// }	
	// }
	// else
	// {

	// }
}

void	mouse_checker(mlx_t *mlx, t_movement *move)
{
	int	movement[2];

}


void	rendering_loop(void *param)
{
	t_transfer	*transporter;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
	t_map		*map;
	
	default_movement(&move);
	transporter = param;
	mlx = transporter->mlx;
	map = transporter->map;
	img = transporter->img;
	key_checker(mlx, &move);
	mouse_checker(mlx, &move);
	ft_bzero(img->pixels, (WIDTH * HEIGHT * sizeof(u_int32_t)));
	//printf("x = %i and y %i\n", move.x, move.y);
	mlx_put_pixel(img, move->x, move->y, 0xff0000ff);
	mlx_image_to_window(mlx, img, 0, 0);
	//mlx_put_string(mlx, "hello",150,150);
}

int	mlx_setup(int *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_transfer	transporter;

	mlx = mlx_init(WIDTH, HEIGHT, "map", 1);
	if (mlx == NULL)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_loop_hook(mlx, &rendering_loop, &transporter);
	transporter.mlx = mlx;
	transporter.img = img;
	transporter.map = map;
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main_casting()// input map
{
	int tmp_map[] = {1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,};
	// get_real_map() and if false return error->exit
	mlx_setup(tmp_map);
	return (0);
}
