/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/16 13:58:30 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static bool	load_sprites_player(mlx_texture_t **player)
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
		free(tmp);
		free(idx);
		player[i] = mlx_load_png(path);
		if (!player[i])
		{
			while (--i >= 0)
			{
				mlx_delete_texture(player[i]);
				player[i] = NULL;
			}
			player = NULL;
			free(path);
			return (false);
		}
		free(path);
		i++;
	}
	return (true);
}

bool	load_sprites(t_sprite *sprite)
{
	if (!load_sprites_player(sprite->player))
		return (false);
	return (true);
}

bool	load_textures(t_input *input, t_texture *texture)
{
	int				i;
	mlx_texture_t	*tex[4];

	texture->wall_no = mlx_load_png(input->tex_no);
	texture->wall_so = mlx_load_png(input->tex_so);
	texture->wall_we = mlx_load_png(input->tex_we);
	texture->wall_ea = mlx_load_png(input->tex_ea);
	tex[0] = texture->wall_no;
	tex[1] = texture->wall_so;
	tex[2] = texture->wall_we;
	tex[3] = texture->wall_ea;
	i = 0;
	while (i < 4 && tex[i])
		i++;
	if (i == 4)
		return (true);
	return (false);
}

void	init(t_data *data)
{
	data->player->player_x = 0;
	data->player->player_y = 0;
	data->player->player_dir = 0;
}
