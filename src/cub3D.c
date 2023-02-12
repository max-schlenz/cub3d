/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/12 02:44:18 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc == 2)
	{
		check_inputfile(MAPNAME);
		data = alloc();
		init(data);
		if (parse_input(data, data->input, data->player, data->map)
			&& check_input(data->input, data->player, data->map))
		{
			load_textures(data->input, data->texture);
			load_sprites(data->sprite);
			main_casting(data);
		}
		cleanup(data);
		exit (EXIT_SUCCESS);
	}
	ft_putendl_fd(HELP, STDERR_FILENO);
	exit (EXIT_FAILURE);
}