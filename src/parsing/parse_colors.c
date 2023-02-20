/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:59:22 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 16:44:54 by mschlenz         ###   ########.fr       */
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
			return (error(0, 0, COLOR_ERROR));
		i++;
	}
	return (true);
}

bool	parse_colors(t_input *input, t_map *map)
{
	int	*ceiling;
	int	*floor;

	ceiling = parse_color(input->c);
	floor = parse_color(input->f);
	if (!check_color_valid(ceiling) || !check_color_valid(floor))
	{
		free (ceiling);
		free (floor);
		return (false);
	}
	map->color_ceiling = get_rgba(ceiling[0], ceiling[1], ceiling[2], 255);
	map->color_floor = get_rgba(floor[0], floor[1], floor[2], 255);
	free (ceiling);
	free (floor);
	return (true);
}
