/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:42:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/18 13:26:10 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	check_player(t_player *player)
{
	if (!player->player_dir)
		return (error(0, 0, PLAYER_ERROR));
	return (true);
}

bool	check_tex_color(t_input *input, t_player *player, t_map *map)
{
	if (!input->tex_no
		|| !input->tex_so
		|| !input->tex_we
		|| !input->tex_ea
		|| !input->f
		|| !input->c)
		return (error(0, 0, PARAM_ERROR));
	return (true);
}

bool	check_elem(char **elem, int row, int col, int params[2])
{
	if ((elem[row][col] == '0'
		|| elem[row][col] == 'd' || elem[row][col] == 'D')
		&& (row == 0 || col == 0
		|| row == params[0] - 1 || col == params[1] - 1
		|| !elem[row][col + 1]
		|| elem[row - 1][col] == '2'
		|| elem[row][col - 1] == '2'
		|| elem[row + 1][col] == '2'
		|| elem[row][col + 1] == '2'))
		return (error(row, col, MAP_ERROR));
	return (true);
}

bool	check_colors(t_input *input)
{
	if (check_color(input->c)
		&& check_color(input->f)
		&& color_count_elems(input->c)
		&& color_count_elems(input->f))
		return (true);
	ft_putendl_fd("Error parsing floor/ceiling color", 2);
	return (false);
}

// static bool	check_line(char *line)
// {
// 	int		i;
// 	int		j;
// 	char	valid[10];

// 	valid[10] = "012NSEWDd";
// 	i = 0;
// 	while (line[i])
// 	{
// 		j = 0;
// 		while (j < 9 && line[i] == valid[j])
// 			j++;
// 		if (j == 10)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

bool	check_input(t_input *input, t_player *player, t_map *map)
{
	int	row;
	int	col;
	int	map_params[2];	

	row = 0;
	col = 0;
	map_params[0] = map->height;
	map_params[1] = map->width;
	if (!check_player(player))
	{
		return (false);
	}
	if (!check_colors(input))
		return (false);
	if (!check_tex_color(input, player, map))
		return (false);
	while (row < map->height && col < map->width)
	{
		if (!check_elem(map->elem, row, col, map_params))
			return (false);
		if (++col == map->width)
		{
			col = 0;
			row++;
		}
	}
	return (true);
}
