/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 13:23:28 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	*parse_color(char *str_input)
{
	char	**str;
	int		*color;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_split(str_input, ',');
	color = ft_calloc(3, sizeof(int));
	while (i < 3)
	{
		tmp = ft_strtrim(str[i], " ");
		free(str[i]);
		if (!ft_strlen(tmp))
			color[i] = -1;
		else
			color[i] = ft_atoi(tmp);
		free (tmp);
		i++;
	}
	free (str);
	return (color);
}

bool	check_color_valid(int rgb[3])
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
	if (!check_color_valid(ceiling) || !check_color_valid(floor))
		return (false);
	map->color_ceiling = get_rgba(ceiling[0], ceiling[1], ceiling[2], 255);
	map->color_floor = get_rgba(floor[0], floor[1], floor[2], 255);
	free (ceiling);
	free (floor);
	return (true);
}

static void	print_controls(void)
{
	ft_putendl_fd("------------------------------", 2);
	ft_putendl_fd("	    cub3D", 2);
	ft_putendl_fd("------------------------------", 2);
	ft_putendl_fd("w/a/s/d\t- Directional movement", 2);
	ft_putendl_fd("mouse\t- Camera movement", 2);
	ft_putendl_fd("shift\t- Run", 2);
	ft_putendl_fd("esc\t- Quit\n", 2);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc == 2 || DEBUG)
	{
		check_inputfile(MAPNAME);
		data = alloc();
		init(data);
		if (parse_input(data->input, data->player, data->map, MAPNAME) \
			&& check_input(data->input, data->player, data->map) \
			&& load_textures(data->input, data->texture) \
			&& load_sprites(data->sprites) \
			&& parse_colors(data->input, data->map))
		{
			// parse_debug(data->input, data->player, data->map);
			print_controls();
			main_casting(data);
		}
		cleanup(data);
		exit (EXIT_SUCCESS);
	}
	ft_putendl_fd(HELP, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
