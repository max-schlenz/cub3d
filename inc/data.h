/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:29:23 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 15:06:34 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <cub3D.h>

typedef struct s_parse
{
	int		map_width;
	int		map_height;
	char	**array;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	*f;
	char	*c;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_parse;

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
	double	top_down;
	double	velocity;//? settig value
	double	rotation_speed;//? settig value
}t_movement;

/**
 * @brief just a struct to parse  multiple structure to the loop
 * 			NOT used afte it. maybe replace it with  a void *array[n]
 * 
 */
typedef struct s_transfer{
	t_parse		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_movement	*move;
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