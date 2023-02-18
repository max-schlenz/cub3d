/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:16:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/18 17:09:19 by mschlenz         ###   ########.fr       */
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

void	alloc_sprite(t_data *data)
{
	data->sprites = ft_calloc(1, sizeof(t_sprite));
	if (!data->sprites)
	{
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

t_sprite	*alloc_sprite_name(t_data *data, int max)
{
	t_sprite	*new;

	new = ft_calloc(max, sizeof(mlx_texture_t *));
	if (!new)
	{
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
	return (new);
}

void	alloc_sprite_player(t_data *data)
{
	data->sprites->player = ft_calloc(34, sizeof(mlx_texture_t *));
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
