/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:17:57 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/07 19:48:58 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	parse_input_player(char **read_buf, t_player *player, int line, int *i)
{
	if (player->player_dir != 0)
		return (error(line, *i, UNEXPECTED_ERROR));
	player->player_x = (*i);
	player->player_y = line;
	player->player_dir = (*read_buf)[(*i)];
	(*read_buf)[(*i)] = '0';
	return (true);
}

bool	parse_input_map(char **read_buf, t_player *player, t_map *map)
{
	static int	line = 0;
	int			i;

	i = 0;
	while ((*read_buf) && (*read_buf)[i] && (*read_buf)[i] != '\n')
	{
		if (line < map->height)
		{
			if (((*read_buf)[i] == 'N' || (*read_buf)[i] == 'S'
				|| (*read_buf)[i] == 'W' || (*read_buf)[i] == 'E')
				&& !parse_input_player(read_buf, player, line, &i))
				return (false);
			if ((*read_buf)[i] == ' ')
				(*read_buf)[i] = '2';
			map->elem[line][i] = (*read_buf)[i];
		}
		i++;
	}
	line++;
	return (true);
}

bool	parse_line(char **line, t_input *input, t_player *player, t_map *map)
{
	if (((*line)[0] == '1' || (*line)[0] == '0' || (*line)[0] == ' ')
		&& !parse_input_map(line, player, map))
		return (false);
	else if (!input->tex_no && !ft_strncmp((*line), "NO ", 3))
		input->tex_no = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_so && !ft_strncmp((*line), "SO ", 3))
		input->tex_so = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_we && !ft_strncmp((*line), "WE ", 3))
		input->tex_we = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_ea && !ft_strncmp((*line), "EA ", 3))
		input->tex_ea = ft_strdup_nonl((*line) + 3);
	else if (!input->f && !ft_strncmp((*line), "F ", 2))
		input->f = ft_strdup_nonl((*line) + 2);
	else if (!input->c && !ft_strncmp((*line), "C ", 2))
		input->c = ft_strdup_nonl((*line) + 2);
	return (true);
}

bool	parse_input(t_data *data, t_input *input, t_player *player, t_map *map)
{
	int		fd;
	char	*line;

	line = ft_calloc(1, sizeof(char));
	if (line && map->width != -1)
	{
		fd = open(MAPNAME, O_RDONLY);
		while (line)
		{
			free (line);
			line = get_next_line(fd);
			if (!line)
				break ;
			if (!parse_line(&line, input, player, map))
				return (false);
		}
	}
	parse_debug(input, player, map);
	return (true);
}
