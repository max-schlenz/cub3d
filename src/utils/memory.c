/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 00:50:17 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 12:21:19 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	alloc_input(t_data *data)
{
	data->input = ft_calloc(1, sizeof(t_input));
	if (!data->input)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
}

static void	alloc_player(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
	{
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

static void	alloc_map(t_data *data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
	{
		// free(data->sprite->player);
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

static void	alloc_map_elem(t_data *data)
{
	data->map->elem = prep_map(data->map);
	if (!data->map->elem)
	{
		free(data->map);
		// free(data->sprite->player);
		free(data->sprites);
		free(data->texture);
		free(data->player);
		free(data->input);
		free(data);
		exit(EXIT_FAILURE);
	}
}

t_data	*alloc(void)
{
	t_data		*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	alloc_input(data);
	alloc_player(data);
	alloc_texture(data);
	alloc_sprite(data);
	alloc_map(data);
	alloc_map_elem(data);
	return (data);
}
