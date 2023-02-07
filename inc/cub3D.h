/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/07 15:44:27 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <math.h>
# include <libft.h>
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
int		main_casting(t_parse *parse, t_texture *tex);
void	parse_map(t_parse *parse);
bool	is_map_valid(t_parse *parse);
void	is_there_something(t_parse *map, t_movement *move);
int		wall_check(t_parse *map, t_movement *move, int f_b, int l_r);
void	key_checker(mlx_t *mlx, t_movement *move);
void	draw_map(t_parse *map, mlx_image_t *img, t_movement *move, t_texture *tex);
void	mouse_checker(mlx_t *mlx, t_movement *move);
char	*ft_strdup_nonl(const char *s1);
void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_parse *map, t_texture *tex);
void	show_player_anim(t_texture *tex, mlx_image_t *img, int x, int y);

#endif
