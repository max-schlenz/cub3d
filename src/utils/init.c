/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 12:08:13 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static bool	free_player(mlx_texture_t **player, int *i)
{
	while (--(*i) >= 0)
	{
		mlx_delete_texture(player[(*i)]);
		player[(*i)] = NULL;
	}
	player = NULL;
	return (false);
}

static bool	load_sprites_folder(t_anim *anim, char *name, int max)
{
	int			i;
	char		*idx;
	char		*tmp;
	char		*path;

	i = 0;
	anim->frames = ft_calloc(max, sizeof(mlx_texture_t *));
	anim->max = max;
	while (i < max)
	{
		idx = ft_itoa(i);
		tmp = ft_strjoin(name, idx);
		path = ft_strjoin(tmp, ".png");
		free_null(2, &tmp, &idx);
		anim->frames[i] = mlx_load_png(path);
		if (!anim->frames[i])
			return (free(path), free_player(anim->frames, &i));
		free(path);
		i++;
	}
	return (true);
}

bool	load_sprites(t_sprites *sprites)
{
	if (!load_sprites_folder(sprites->player, "res/player/sprite", 33))
		return (false);
	return (true);
}

bool	load_textures(t_input *input, t_texture *texture)
{
	int				i;
	mlx_texture_t	*tex[6];

	texture->wall_no = mlx_load_png(input->tex_no);
	texture->wall_so = mlx_load_png(input->tex_so);
	texture->wall_we = mlx_load_png(input->tex_we);
	texture->wall_ea = mlx_load_png(input->tex_ea);
	texture->open_door = mlx_load_png(input->tex_door_open);
	texture->closed_door = mlx_load_png(input->tex_door_closed);
	tex[0] = texture->wall_no;
	tex[1] = texture->wall_so;
	tex[2] = texture->wall_we;
	tex[3] = texture->wall_ea;
	tex[4] = texture->open_door;
	tex[5] = texture->closed_door;
	i = 0;
	while (i < 6 && tex[i])
		i++;
	if (i == 6)
		return (true);
	return (error(0, 0, TEXTURE_ERROR));
}

void	init(t_data *data)
{
	data->player->player_x = 0;
	data->player->player_y = 0;
	data->player->player_dir = 0;
}
