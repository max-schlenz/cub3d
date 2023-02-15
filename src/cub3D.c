/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/15 17:18:15 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static int*	parse_color(char *str_input)
{
	char	**str;
	int		*color;
	char	*tmp;
	
	str = ft_split(str_input, ',');
	color = ft_calloc(3, sizeof(int));
	for (int i = 0; i < 3; i++)
	{
		tmp = ft_strtrim(str[i], " ");
		color[i] = ft_atoi(tmp);
		free (tmp);
	}
	return (color);
}

static void	parse_colors(t_input *input, t_map *map)
{
	int	*ceiling;
	int	*floor;

	ceiling = parse_color(input->c);
	floor = parse_color(input->f);
	map->color_ceiling = get_rgba(ceiling[0], ceiling[1], ceiling[2], 255);
	map->color_floor = get_rgba(floor[0], floor[1], floor[2], 255);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc == 2 || DEBUG)
	{
		check_inputfile(MAPNAME);
		data = alloc();
		init(data);
		if (parse_input(data, data->input, data->player, data->map)
			&& check_input(data->input, data->player, data->map))
		{
			parse_colors(data->input, data->map);
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
