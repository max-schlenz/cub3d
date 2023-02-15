/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/15 18:25:43 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <data.h>
# include "hex_color.h"

# define PLAYER_SPRITE_FRAMES
# define MAPNAME "maps/test"
# define DEBUG 1
# define HELP "./cub3d <filepath>\n"

/**
 * @brief main function for the raycasting part
 * 
 */
int		main_casting(t_data *data);
bool	parse_input(t_data *data, t_input *input, t_player *player, t_map *map);
bool	check_input(t_input *input, t_player *player, t_map *map);
void	is_there_something(t_map *map, t_movement *move);
int		wall_check(t_map *map, t_movement *move, int f_b, int l_r);
void	key_checker(mlx_t *mlx, t_movement *move, t_map *map);
void	draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_texture *tex, t_sprite *sprite);
void	mouse_checker(mlx_t *mlx, t_movement *move, mlx_image_t *img_bg);
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
char	**prep_map(t_map *map);
void	overshot_protection(double *degree);
void	img_draw_char(mlx_image_t* image, int32_t texoffset, int32_t imgoffset);
void	update_fps_counter(mlx_t* mlx, mlx_image_t* img);
void	parse_debug(t_input *input, t_player *player, t_map *map);
void 	render_ceiling_floor(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex);
void	draw_hori(mlx_image_t *img, int y, uint32_t col);
void	project(mlx_t *mlx, mlx_image_t *img_bg, t_movement *move, t_map *map, t_texture *tex);
void 	draw_pixel(uint8_t* pixel, uint32_t color);
void	init_data(t_data *data);
void	alloc_texture(t_data *data);
void	alloc_sprite(t_data *data);
void	alloc_sprite_player(t_data *data);
void	check_inputfile(char *path);

#endif
