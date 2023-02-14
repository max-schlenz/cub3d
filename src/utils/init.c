/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/14 11:28:26 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	load_sprites_player(mlx_texture_t **player)
{
	int		i;
	char	*idx;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < 33)
	{
		idx = ft_itoa(i);
		tmp = ft_strjoin("res/player/sprite", idx);
		path = ft_strjoin(tmp, ".png");
		player[i++] = mlx_load_png(path);
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
	texture->wall_no = mlx_load_png(input->tex_no);
	//texture->wall_no = mlx_load_png("./res/alien-invasion-apocalypse-sci-fi-collapse-wallpaper-preview.png");
	texture->wall_so = mlx_load_png(input->tex_so);
	texture->wall_we = mlx_load_png(input->tex_we);
	texture->wall_ea = mlx_load_png(input->tex_ea);
}

void	init(t_data *data)
{
	data->player->near_obj = 0;
	data->player->player_x = 0;
	data->player->player_y = 0;
	data->player->player_dir = 0;
}
