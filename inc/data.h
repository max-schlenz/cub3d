/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:29:23 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/12 01:58:35 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <cub3D.h>

typedef enum e_transport
{
	MLX,
	MAP,
	IMG,
	IMG_BG,
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
	UNEXPECTED_ERROR
}	t_error;

typedef struct s_sprite
{
	mlx_texture_t	**player;
}	t_sprite;

typedef struct s_texture
{
	mlx_texture_t	*wall_no;
	mlx_texture_t	*wall_so;
	mlx_texture_t	*wall_we;
	mlx_texture_t	*wall_ea;
}	t_texture;

typedef struct s_input
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
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
}	t_map;

typedef struct s_data
{
	t_input		*input;
	t_player	*player;
	t_map		*map;
	t_texture	*texture;
	t_sprite	*sprite;
}	t_data;

/**
 * @brief base struct for map movement related vars
 * 
 * @param x x position on the map
 * @param y y position on the map
 * 
 * @param tile_x x position inside of a tile(0 - 1)
 * @param tile_y y position inside of a tile(0 - 1)
 * 
 * @param direction the direction the player looks on the horizontal axis, value is i radial (0 - 2 pi)
 * @param velocity value how fast the player can move //?setting value 
 * @param rotation_speed value how fast a  player can turn//? setting value
 */
typedef struct s_movement{
	int		x;
	int		y;
	double	tile_x;
	double	tile_y;
	double	direction;
	int		top_down;
	double	velocity;//? settig value
	double	rotation_speed;//? settig value
	int		pixel_per_map_tile;
}t_movement;

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
	t_movement	*move;
	t_texture	*tex;
	t_player	*player;
	t_sprite	*sprite;
}t_transfer;

/**
 * @brief 	//! NOT IN USE YET
 * 			base idee for to store the info after raycasting
 * 
 * 
 */
typedef struct s_array
{
	int				x;
	double			tile_x;
	double			direction;
	double			distance;
	mlx_texture_t	*texture;
}t_array;

#endif