/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/08 00:03:00 by mschlenz         ###   ########.fr       */
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
int		main_casting(t_data *data);
bool	parse_input(t_input *input, t_player *player, t_map *map);
bool	input_valid(t_input *input, t_player *player, t_map *map);
void	is_there_something(t_map *map, t_movement *move);
int		wall_check(t_map *map, t_movement *move, int f_b, int l_r);
void	key_checker(mlx_t *mlx, t_movement *move);
void	draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite);
void	mouse_checker(mlx_t *mlx, t_movement *move);
char	*ft_strdup_nonl(const char *s1);
void	raycasting(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex);
void	show_player_anim(mlx_texture_t **player, mlx_image_t *img, int x, int y);
void	cleanup(t_data *data);
void	load_textures(t_input *input, t_texture *tex);
void	load_sprites(t_sprite *sprite);
void	init(t_data *data);
t_data	*alloc(void);
bool	error(int row, int col, t_error error);
char	*get_line(int fd);

#endif
