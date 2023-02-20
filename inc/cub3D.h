/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 14:21:23 by mschlenz         ###   ########.fr       */
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
# include <define_default.h>

# define PLAYER_SPRITE_FRAMES
# define MAPNAME "maps/pixel.cub"
# define DEBUG 1
# define HELP "./cub3d <filepath>"


/**
 * @brief main function for the raycasting part
 * 
 */
int			main_casting(t_data *data);
bool		parse_input(t_input *input, t_player *player, t_map *map, char *path);
bool		check_input(t_input *input, t_player *player, t_map *map);
void		is_there_something(t_map *map, t_movement *move);
int			wall_check(t_map *map, t_movement *move, int f_b, int l_r);
void		key_checker(mlx_t *mlx, t_movement *move, t_map *map);
void		draw_map(t_map *map, mlx_image_t *img, t_movement *move, t_sprites *sprites);
void		mouse_checker(mlx_t *mlx, t_movement *move);
char		*ft_strdup_nonl(const char *s1);
void		raycasting( mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex);
void		show_anim_sprite(t_anim *anim, mlx_image_t *img, int x, int y);
void		cleanup(t_data *data);
bool		load_textures(t_input *input, t_texture *tex);
bool		load_sprites(t_sprites *frames);
void		init(t_data *data);
t_data		*alloc(void);
bool		error(int row, int col, t_error error);
char		*get_line(int fd);
char		**prep_map(t_map *map);
void		overshot_protection(double *degree);
void		img_draw_char(mlx_image_t* image, int32_t texoffset, int32_t imgoffset);
void		update_fps_counter(mlx_t* mlx, mlx_image_t* img);
void		parse_debug(t_input *input, t_player *player, t_map *map);
void 		render_ceiling_floor(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex);
void		draw_hori(mlx_image_t *img, int y, uint32_t col);
mlx_image_t	*create_bg_layer(mlx_t *mlx, int color_ceiling, int color_floor);
void 		draw_pixel(uint8_t* pixel, uint32_t color);
void		init_data(t_data *data);
void		alloc_texture(t_data *data);
void		alloc_sprite(t_data *data);
void		alloc_sprite_player(t_data *data);
void		check_inputfile(char *path);
int			img_pixel(double x_p, double y_p, mlx_texture_t *tex);
int			left_turn(t_movement *move);
int			right_turn(t_movement *move);
int			front_tile(t_map *map, t_movement *move);
int			back_tile(t_map *map, t_movement *move);
int			usedda_ultra(t_dda *dda_h, t_dda *dda_v, t_map *map);
void		dda_info_v(int y, double direction, \
double		*player, t_dda *dda_info);
void		dda_info_h(int x, double direction, \
double		*player, t_dda *dda_info);
void		draw_wall(t_array *test, mlx_image_t *img, double fov);
bool		color_count_elems(char *str_input);
bool		check_color(char *str);
void		update_fps_counter(mlx_t *mlx, mlx_image_t *img);
void		choose_frame(t_sprites *sprites, mlx_t *mlx);
void		alloc_sprite_door_locked(t_data *data);
void		alloc_sprite_door_opened(t_data *data);
void		draw_anim(t_tile tile, mlx_image_t *img, t_sprites *sprites);
bool		parse_colors(t_input *input, t_map *map);
void		print_controls(void);

#endif
