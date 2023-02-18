/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/18 08:04:57 by lkrabbe          ###   ########.fr       */
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
		if (!ft_strlen(tmp))
			color[i] = -1;
		else
			color[i] = ft_atoi(tmp);
		free (tmp);
	}
	return (color);
}

static bool	check_color(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] == -1 || rgb[i] > 255 || rgb[i] < 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	parse_colors(t_input *input, t_map *map)
{
	int	*ceiling;
	int	*floor;

	ceiling = parse_color(input->c);
	floor = parse_color(input->f);
	if (!check_color(ceiling) || !check_color(floor))
		return (false);
	map->color_ceiling = get_rgba(ceiling[0], ceiling[1], ceiling[2], 255);
	map->color_floor = get_rgba(floor[0], floor[1], floor[2], 255);
	free (ceiling);
	free (floor);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc == 2 || DEBUG)
	{
		check_inputfile(MAPNAME);
		data = alloc();
		init(data);
		if ((parse_input(data, data->input, data->player, data->map, MAPNAME)
			&& check_input(data->input, data->player, data->map)
			&& load_textures(data->input, data->texture)
			&& load_sprites(data->sprite))
			&& parse_colors(data->input, data->map))
				main_casting(data);
		cleanup(data);
		exit (EXIT_SUCCESS);
	}
	ft_putendl_fd(HELP, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
