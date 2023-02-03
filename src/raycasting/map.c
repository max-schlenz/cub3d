
#include	"../../MLX42/include/MLX42/MLX42.h"
#include	<stdio.h>
#include	"math.h"
#include	<fcntl.h>
#include	<stdlib.h>

# define WIDTH 200 
# define HEIGHT 200 

# define X 0 //enum???

# define Y 1

# define VELOCITY = 0.1



typedef struct s_value{
	double	cords[4];
	t_color	color;
	int		screen[4];
}t_points;

void	set_to_default(t_default *default)
{
	default->
}

void	key_checker()
{
	int	movement[2];

	if (mlx_is_key_down(a_s->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(a_s->mlx);
	if (mlx_is_key_down(a_s->mlx, MLX_KEY_W))
		movement[X] = velocity;
	if (mlx_is_key_down(a_s->mlx, MLX_KEY_A))
		a_s->input->input[y_scale] += boost * 10 * caps_check(a_s->mlx);
	if (mlx_is_key_down(a_s->mlx, MLX_KEY_s))
		a_s->input->input[z_scale] += boost * caps_check(a_s->mlx);
}

void	rendering_loop(void *param)
{
	mlx_t	*mlx = param;

	mlx_put_string(mlx, "hello",150,150);
}

int	mlx_setup(int *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "map", 1);
	if (mlx == NULL)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_loop_hook(mlx, &rendering_loop, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main()// input map
{
	int tmp_map[] = {1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,};
	// get_real_map() and if false return error->exit
	mlx_setup(tmp_map);
	return (0);
}
