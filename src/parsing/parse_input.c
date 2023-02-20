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

static bool	check_line(char *line)
{
	int			i;
	int			j;
	const char	valid[11] = "012NSEWDd \n";

	i = 0;
	if (!line || (line && line[0] && line[0] == '\n'))
		return (false);
	while (line[i])
	{
		j = 0;
		while (j < 11 && line[i] != valid[j])
			j++;
		if (j == 11)
			return (false);
		i++;
	}
	return (true);
}

bool	parse_input_map(char **read_buf, t_player *player, t_map *map, bool *m)
{
	static int	line = 0;
	int			i;

	i = 0;
	(*m) = true;
	if (!check_line((*read_buf)))
		return (false);
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
	static bool	bmap = false;

	if (((*line)[0] == '1' || (*line)[0] == '0' || (*line)[0] == ' ' || bmap)
		&& !parse_input_map(line, player, map, &bmap))
		return (false);
	if (!bmap)
	{
		if (!input->tex_no && !ft_strncmp((*line), "NO ", 3))
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
		else if (!input->tex_door_closed && !ft_strncmp((*line), "D ", 2))
			input->tex_door_closed = ft_strdup_nonl((*line) + 2);
		else if (!input->tex_door_open && !ft_strncmp((*line), "d ", 2))
			input->tex_door_open = ft_strdup_nonl((*line) + 2);
	}
	return (true);
}

bool	parse_input(t_input *input, t_player *player, t_map *map, char *path)
{
	int		fd;
	char	*line;

	line = ft_calloc(1, sizeof(char));
	if (line && map->width != -1)
	{
		fd = open(path, O_RDONLY);
		while (line)
		{
			free (line);
			line = get_next_line(fd);
			if (!line)
				break ;
			if (!parse_line(&line, input, player, map))
				return (error(0, 0, MAP_ERROR));
		}
	}
	return (true);
}
