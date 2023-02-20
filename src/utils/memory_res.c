/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:16:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 15:20:17 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	alloc_texture(t_data *data)
{
	data->texture = ft_calloc(1, sizeof(t_texture));
	if (!data->texture)
	{
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

void	alloc_sprite_door_locked(t_data *data)
{
	data->sprites->door_locked = ft_calloc(1, sizeof(t_anim));
	if (!data->sprites->door_locked)
	{
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

void	alloc_sprite_door_opened(t_data *data)
{
	data->sprites->door_opened = ft_calloc(1, sizeof(t_anim));
	if (!data->sprites->door_opened)
	{
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

void	alloc_sprite_player(t_data *data)
{
	data->sprites->player = ft_calloc(1, sizeof(t_anim));
	if (!data->sprites->player)
	{
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

void	alloc_sprite(t_data *data)
{
	data->sprites = ft_calloc(1, sizeof(t_sprites));
	if (!data->sprites)
	{
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}
