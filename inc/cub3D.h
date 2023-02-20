/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:56:28 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 15:52:50 by mschlenz         ###   ########.fr       */
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
# include <define_default.h>

# define PLAYER_SPRITE_FRAMES
# define MAPNAME "maps/pixel.cub"
# define DEBUG 1
# define HELP "./cub3d <filepath>"

//src/cub3D.c
int				main(int argc, char **argv);
void			print_controls(void);

//src/debug.c
void			parse_debug(t_input *input, t_player *player, t_map *map);

//src/draw_on_screen/draw_anims.c
void			choose_frame(t_sprites *sprites, mlx_t *mlx);
void			draw_anim(t_tile tile, mlx_image_t *img, t_sprites *sprites);
void			next_sprite(t_anim *anim);
void			show_anim_sprite(t_anim *anim, mlx_image_t *img, int x, int y);

//src/draw_on_screen/draw_map.c
int				what_tile(t_map *map, t_movement *move, int x, int y);
void			draw_map(t_map *map, mlx_image_t *img, t_movement *move,
					t_sprites *sprites);
void			draw_tile(mlx_image_t *img, t_tile *tile, int color);

//src/draw_on_screen/draw_wall.c
int				get_color(uint8_t *start);
int				img_pixel(double x_p, double y_p, mlx_texture_t *tex);
void			draw_wall(t_array *test, mlx_image_t *img, double fov);

//src/map_movement/arrow_keys.c
int				back_tile(t_map *map, t_movement *move);
int				front_tile(t_map *map, t_movement *move);
int				left_turn(t_movement *move);
int				right_turn(t_movement *move);
void			try_to_move(t_map *map, t_movement *move, int x, int y);

//src/map_movement/check_side.c
void			check_east(t_map *map, t_movement *move);
void			check_north(t_map *map, t_movement *move);
void			check_south(t_map *map, t_movement *move);
void			check_west(t_map *map, t_movement *move);
void			is_there_something(t_map *map, t_movement *move);

//src/map_movement/checks.c
int				wall_check(t_map *map, t_movement *move, int f_b, int l_r);

//src/map_movement/key_input.c
void			arrow_keys(mlx_t *mlx, t_map *map, t_movement *move);
void			easy_move(double *movement, t_movement *move, double dir);
void			key_checker(mlx_t *mlx, t_movement *move, t_map *map);
void			wasd_keys(t_movement *move, mlx_t *mlx);

//src/map_movement/mouse_input.c
void			mouse_checker(mlx_t *mlx, t_movement *move);
void			overshot_protection(double *degree);

//src/not_used_funtions.c
void			matrix_two(double *array, double degree);

//src/parsing/parse_check.c
bool			check_colors(t_input *input);
bool			check_elem(char **elem, int row, int col, int params[2]);
bool			check_input(t_input *input, t_player *player, t_map *map);
bool			check_player(t_player *player);
bool			check_tex_color(t_input *input);

//src/parsing/parse_colors.c
bool			check_color_valid(int rgb[3]);
bool			parse_colors(t_input *input, t_map *map);
int				get_rgba(int r, int g, int b, int a);

//src/parsing/parse_input.c
bool			parse_input(t_input *input, t_player *player, t_map *map,
					char *path);
bool			parse_input_map(char **read_buf, t_player *player, t_map *map,
					bool *m);
bool			parse_input_player(char **read_buf, t_player *player, int line,
					int *i);
bool			parse_line(char **line, t_input *input, t_player *player,
					t_map *map);

//src/parsing/parse_utils.c
bool			error(int row, int col, t_error error);
char			*ft_strdup_nonl(const char *s1);

//src/raycasting/dda.c
int				usedda_h(t_dda *dda_info, t_map *map);
int				usedda_ultra(t_dda *dda_h, t_dda *dda_v, t_map *map);
int				usedda_v(t_dda *dda_info, t_map *map);
void			dda_info_h(int x, double direction, double *player,
					t_dda *dda_info);
void			dda_info_v(int y, double direction, double *player,
					t_dda *dda_info);

//src/raycasting/map.c
int				main_casting(t_data *data);
int				mlx_setup(t_data *data, t_map *map, t_player *player,
					t_texture *tex);
void			default_movement(t_movement *move, mlx_image_t *img,
					t_player *player);
void			rendering_loop(void *param);

//src/raycasting/project.c
void			draw_pixel(uint8_t *pixel, uint32_t color);
void			ft_memset_cub(int *b, uint32_t c, size_t len);
mlx_image_t		*create_bg_layer(mlx_t *mlx, int ceiling, int floor);

//src/raycasting/raycasting.c
void			raycasting(mlx_image_t *img, t_movement *move, t_map *map,
					t_texture *tex);
void			single_ray(t_array *ray, t_map *map, t_texture *tex);
void			use_hori(t_dda *dda_h, t_array *ray, t_map *map,
					t_texture *tex);
void			use_vert(t_dda *dda_v, t_array *ray, t_map *map,
					t_texture *tex);

//src/utils/cleanup.c
void			cleanup(t_data *data);

//src/utils/fps.c
void			update_fps_counter(mlx_t *mlx, mlx_image_t *img);

//src/utils/init.c
bool			load_sprites(t_sprites *sprites);
bool			load_textures(t_input *input, t_texture *texture);
void			init(t_data *data);

//src/utils/memory.c
t_data			*alloc(char *path);

//src/utils/memory_map.c
char			**prep_map(t_map *map, char *path);

//src/utils/memory_res.c
void			alloc_sprite(t_data *data);
void			alloc_sprite_door_locked(t_data *data);
void			alloc_sprite_door_opened(t_data *data);
void			alloc_sprite_player(t_data *data);
void			alloc_texture(t_data *data);

//src/utils/utils.c
bool			check_color(char *str);
bool			color_count_elems(char *str_input);
void			check_inputfile(char *path);
void			img_draw_char(mlx_image_t *image, int32_t texoffset,
					int32_t imgoffset);

#endif
