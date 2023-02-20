/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:16:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 11:45:25 by mschlenz         ###   ########.fr       */
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
	data->sprites = ft_calloc(1, sizeof(t_anim));
	if (!data->sprites)
	{
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

t_anim	*alloc_sprite_name(t_data *data, int max)
{
	t_anim	*new;

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
