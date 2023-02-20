/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:02:42 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 11:45:33 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	clean_sprites(t_anim *sprite)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("%i\n", i);
		mlx_delete_texture(sprite->frames[i++]);
	}
	free(sprite->frames);
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
	if (texture->open_door)
		mlx_delete_texture(texture->open_door);
	if (texture->closed_door)
		mlx_delete_texture(texture->closed_door);
	free(texture);
}

static void	clean_input(t_input *input)
{
	free(input->tex_no);
	free(input->tex_so);
	free(input->tex_we);
	free(input->tex_ea);
	free(input->tex_door_closed);
	free(input->tex_door_open);
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
	// clean_sprites(data->sprites->player);
	clean_map(data->map);
	free(data->player);
	free(data->map);
	free(data);
	return ;
}
