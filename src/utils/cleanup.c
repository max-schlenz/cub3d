/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:02:42 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 15:19:52 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	clean_anim(t_anim *anim)
{
	int	i;

	i = 0;
	while (i < anim->max)
		mlx_delete_texture(anim->frames[i++]);
	free(anim->frames);
	free(anim);
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
	clean_anim(data->sprites->player);
	clean_anim(data->sprites->door_locked);
	clean_anim(data->sprites->door_opened);
	free(data->sprites);
	clean_map(data->map);
	free(data->player);
	free(data->map);
	free(data);
	return ;
}
