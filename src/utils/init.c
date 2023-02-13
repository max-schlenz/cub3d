/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/12 14:09:32 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void load_sprites_player(mlx_texture_t **player)
{
	char	*idx;
	char	*tmp;
	char	*path;

	for (int i = 0; i < 33; i++)
	{
		idx = ft_itoa(i);
		tmp = ft_strjoin("res/player/sprite", idx);
		path = ft_strjoin(tmp, ".png");
		player[i] = mlx_load_png(path);
		free(tmp);
		free(path);
		free(idx);
	}
}

void	load_sprites(t_sprite *sprite)
{
	load_sprites_player(sprite->player);
}

void	load_textures(t_input *input, t_texture *texture)
{
	// texture->wall_no = mlx_load_png(input->tex_no);
	texture->wall_no = mlx_load_png("./res/42.png");
	texture->wall_so = mlx_load_png(input->tex_so);
	texture->wall_we = mlx_load_png(input->tex_we);
	texture->wall_ea = mlx_load_png(input->tex_ea);
}

void	init(t_data *data)
{
	data->player->player_x = 0;
	data->player->player_y = 0;
	data->player->player_dir = 0;
}

t_data	*alloc()
{
	t_data		*data;
	
	data = ft_calloc(1, sizeof(t_data));
	data->input = ft_calloc(1, sizeof(t_input));
	data->player = ft_calloc(1, sizeof(t_player));
	data->texture = ft_calloc(1, sizeof(t_texture));
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	data->sprite->player = ft_calloc(34, sizeof(mlx_texture_t *));
	data->map = ft_calloc(1, sizeof(t_map));
	data->map->elem = alloc_map(data->map);
	return (data);
}
