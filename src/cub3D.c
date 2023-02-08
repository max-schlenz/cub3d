/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/08 01:24:55 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(void)
{
	t_data		*data;

	data = alloc();
	init(data);
	parse_input(data->input, data->player, data->map);
	if (input_valid(data->input, data->player, data->map))
	{
		load_textures(data->input, data->texture);
		load_sprites(data->sprite);
		// main_casting(data);
	}
	cleanup(data);
	return (0);
}