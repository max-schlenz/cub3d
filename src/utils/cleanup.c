/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:02:42 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/12 01:43:48 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	clean_sprites(t_sprite *sprite)
{
	int	i;

	i = 0;
	while (sprite->player[i])
		mlx_delete_texture(sprite->player[i++]);
	free(sprite->player);
	free(sprite);
}

static void	clean_textures(t_texture *texture)
{
	if (texture->wall_no)
		mlx_delete_texture(texture->wall_no);
	if (texture->wall_so)
		mlx_delete_texture(texture->wall_so);
	if (texture->wall_we)
		mlx_delete_texture(texture->wall_we);
	if (texture->wall_ea)
		mlx_delete_texture(texture->wall_ea);
	free(texture);
}

static void	clean_input(t_input *input)
{
	free(input->tex_no);
	free(input->tex_so);
	free(input->tex_we);
	free(input->tex_ea);
	free(input->f);
	free(input->c);
	free(input);
}

static void	clean_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->elem[i])
		free(map->elem[i++]);
	free(map->elem);
}

void	cleanup(t_data *data)
{
	clean_textures(data->texture);
	clean_input(data->input);
	clean_sprites(data->sprite);
	clean_map(data->map);
	free(data->player);
	free(data->map);
	free(data);
	return ;
}