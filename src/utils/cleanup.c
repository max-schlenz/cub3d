/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:02:42 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/07 23:43:44 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

static void clean_sprites(t_sprite *sprite)
{
	for (int i = 0; i < 33 && sprite->player[i]; i++)
		mlx_delete_texture(sprite->player[i]);
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
	free_null(6, &input->tex_no, &input->tex_so, &input->tex_we, &input->tex_ea,
		&input->f, &input->c);
	free(input);
}

static void clean_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
		free(map->elem[i]);
	free(map->elem);
}

void	cleanup(t_data *data)
{
	clean_textures(data->texture);
	clean_input(data->input);
	clean_sprites(data->sprite);
	clean_map(data->map);
	free_null(2, &data->player, &data->map);
	free(data);
	exit (EXIT_SUCCESS);
}