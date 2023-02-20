/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 15:33:56 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	print_controls(void)
{
	ft_putendl_fd("------------------------------", STDOUT_FILENO);
	ft_putendl_fd("	    cub3D", STDOUT_FILENO);
	ft_putendl_fd("------------------------------", STDOUT_FILENO);
	ft_putendl_fd("w/a/s/d\t- Directional movement", STDOUT_FILENO);
	ft_putendl_fd("mouse\t- Camera movement", STDOUT_FILENO);
	ft_putendl_fd("shift\t- Run", STDOUT_FILENO);
	ft_putendl_fd("esc\t- Quit\n", STDOUT_FILENO);
}

static bool	prepare_scene(t_data *data, char *input)
{
	if (parse_input(data->input, data->player, data->map, input) \
	&& check_input(data->input, data->player, data->map) \
	&& load_textures(data->input, data->texture) \
	&& load_sprites(data->sprites) \
	&& parse_colors(data->input, data->map))
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc == 2)
	{
		check_inputfile(argv[1]);
		data = alloc();
		init(data);
		if (prepare_scene(data, argv[1]))
			main_casting(data);
		cleanup(data);
		exit(EXIT_SUCCESS);
	}
	ft_putendl_fd(HELP, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
