/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:20:52 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 16:46:44 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <cub3D.h>

typedef enum e_anims
{
	A_PLAYER,
	A_ODOOR,
	A_LDOOR
}	t_anims;

typedef enum e_transport
{
	MLX,
	MAP,
	IMG,
	IMG_BG,
	IMG_MAP,
	MOVE,
	TEX,
	SPRITE,
	PLAYER
}	t_transport;

typedef enum e_error
{
	MAP_ERROR,
	PARAM_ERROR,
	PLAYER_ERROR,
	TEXTURE_ERROR,
	COLOR_ERROR,
	UNEXPECTED_ERROR
}	t_error;

typedef struct s_anim
{
	int				max;
	int				idx;
	mlx_texture_t	**frames;
}	t_anim;

typedef struct s_sprites
{
	t_anim		*player;
	t_anim		*door_locked;
	t_anim		*door_opened;
}	t_sprites;

typedef struct s_texture
{
	mlx_texture_t	*wall_no;
	mlx_texture_t	*wall_so;
	mlx_texture_t	*wall_we;
	mlx_texture_t	*wall_ea;
	mlx_texture_t	*open_door;
	mlx_texture_t	*closed_door;
}	t_texture;

typedef struct s_input
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	*tex_door_open;
	char	*tex_door_closed;
	char	*f;
	char	*c;
}	t_input;

typedef struct t_player
{
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_player;

typedef struct t_map
{
	char	**elem;
	int		width;
	int		height;
	int		color_ceiling;
	int		color_floor;
}	t_map;

typedef struct s_bool
{
	bool	player;
	bool	door_locked;
}	t_bool;

typedef struct s_data
{
	t_input		*input;
	t_player	*player;
	t_map		*map;
	t_texture	*texture;
	t_sprites	*sprites;
}	t_data;

typedef struct s_movement
{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
	double	direction;
	int		top_down;
	double	velocity;
	double	rotation_speed;
	int		pixel_per_map_tile;
	int		tmp;
}	t_movement;

/**
 * @brief just a struct to parse  multiple structure to the loop
 * 			NOT used afte it. maybe replace it with  a void *array[n]
 * 
 */
typedef struct s_transfer{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_bg;
	mlx_image_t	*img_map;
	t_movement	*move;
	t_texture	*tex;
	t_player	*player;
	t_sprites	*sprites;
}t_transfer;

/**
 * @brief 	//! NOT IN USE YET
 * 			base idee for to store the info after raycasting
 * 
 * 
 */
typedef struct s_array
{
	double			*point;
	int				x;
	double			tile_x;
	double			direction;
	double			distance;
	double			player[3];
	int				player_x;
	int				player_y;
	mlx_texture_t	*texture;
}	t_array;

typedef struct s_dda
{
	double	jump;
	int		(*f_ptr)(struct s_dda *dda_info, t_map *map);
	double	hit[10];
	int		offset;
	int		dir;
}	t_dda;

typedef struct s_tile{
	int	x;
	int	y;
	int	color;
}	t_tile;
#endif
