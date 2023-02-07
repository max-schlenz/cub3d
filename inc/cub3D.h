/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 18:47:18 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <stdlib.h>
# include <stdbool.h>
# include <libft.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <data.h>
# include "hex_color.h"

/**
 * @brief main function for the raycasting part
 * 
 */
int		main_casting(t_parse *parse);
void	parse_map(t_parse *parse);
bool	is_map_valid(t_parse *parse);
void	is_there_something(t_parse *map, t_movement *move);
int		wall_check(t_parse *map, t_movement *move, int f_b, int l_r);
void	key_checker(mlx_t *mlx, t_movement *move);
void	draw_map(t_parse *map, mlx_image_t *img, t_movement *move);
void	mouse_checker(mlx_t *mlx, t_movement *move);
void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_parse *map);

#endif
