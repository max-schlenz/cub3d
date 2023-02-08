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

static bool	get_map_params(t_map *map)
{
	int		fd;
	int		width_line;
	char	*line;

	if (!access("maps/test", F_OK))
	{
		fd = open("maps/test", O_RDONLY);
		line = ft_calloc(1, sizeof(char));
		while (line != NULL)
		{
			free (line);
			line = get_next_line(fd);
			if (!line)
				return (true);
			if (line[0] == '\n'
				|| (line[0] != '0' && line[0] != '1' && line[0] != ' '))
				continue ;
			map->height++;
			width_line = ft_strlen(line) - 1;
			if (width_line > map->width)
				map->width = width_line;
		}
		return (true);
	}
	return (false);
}

char	**alloc_map(t_map *map)
{
	int		i;
	char	**elem;

	i = 0;
	get_map_params(map);
	elem = ft_calloc(map->height + 2, sizeof(char*));
	while (i < map->height)
	{
		elem[i] = ft_calloc(map->width + 2, sizeof(char));
		ft_memset(elem[i++], '2', map->width + 1);
	}
	elem[map->height + 1] = NULL;
	return (elem);
}

bool	input_valid(t_input *input, t_player *player, t_map *map)
{
	int			row;
	int			col;
	const char	**elem = (const char**)map->elem;

	row = 0;
	col = 0;
	if (!player->player_dir)
		return (error(row, col, PLAYER_ERROR));
	if (!input->tex_no || !input->tex_so || !input->tex_we || !input->tex_ea
		|| !input->f || !input->c)
		return (error(0, 0, PARAM_ERROR));
	while (row < map->height && col < map->width)
	{
		if (elem[row][col] == '0' && (
				row == 0 || col == 0 || row == map->height - 1
				|| col == map->width - 1 || !elem[row][col + 1]
				|| elem[row - 1][col] == '2' || elem[row][col - 1] == '2'
				|| elem[row + 1][col] == '2' || elem[row][col + 1] == '2'))
			return (error(row, col, MAP_ERROR));
		if (++col == map->width)
		{
			col = 0;
			row++;
		}
	}
	return (true);
}

void	parse_input_player(char **read_buf, t_player *player, int line, int *i)
{
	if (player->player_dir != 0)
	{
		printf("Error: multiple player spawns (line: %i, row: %i)\n", line, (*i));
		exit (0);
	}
	player->player_x = (*i);
	player->player_y = line;
	player->player_dir = (*read_buf)[(*i)];
}

void	parse_input_map(char **read_buf, t_player *player, t_map *map)
{
	static int	line = 0;
	int			i;

	i = 0;
	while ((*read_buf) && (*read_buf)[i] && (*read_buf)[i] != '\n')
	{
		if (line < map->height)
		{
			if ((*read_buf)[i] == 'N' || (*read_buf)[i] == 'S' 
				|| (*read_buf)[i] == 'W' || (*read_buf)[i] == 'E')
				parse_input_player(read_buf, player, line, &i);
			if ((*read_buf)[i] == ' ')
				(*read_buf)[i] = '2';
			map->elem[line][i] = (*read_buf)[i];
		}
		i++;
	}
	line++;
}


static void	parse_debug(t_input *input, t_player *player, t_map *map)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
			printf("%c", map->elem[i][j]);
		printf("\n");
	}

	printf("\nWIDTH: %i, HEIGHT: %i\n", map->width, map->height);
	printf("tex_no: %s\n", input->tex_no);
	printf("tex_so: %s\n", input->tex_so);
	printf("tex_we: %s\n", input->tex_we);
	printf("tex_ea: %s\n", input->tex_ea);
	printf("f: %s\n", input->f);
	printf("c: %s\n", input->c);
	printf("player_x: %i\n", player->player_x);
	printf("player_y: %i\n", player->player_y);
	printf("player_dir: %c\n", player->player_dir);
}

static void	parse_line(char **line, t_input *input, t_player *player, t_map *map)
{
	if (!input->tex_no && !ft_strncmp((*line), "NO", 2))
		input->tex_no = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_so && !ft_strncmp((*line), "SO", 2))
		input->tex_so = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_we && !ft_strncmp((*line), "WE", 2))
		input->tex_we = ft_strdup_nonl((*line) + 3);
	else if (!input->tex_ea && !ft_strncmp((*line), "EA", 2))
		input->tex_ea = ft_strdup_nonl((*line) + 3);
	else if (!input->f && !ft_strncmp((*line), "F", 1))
		input->f = ft_strdup_nonl((*line) + 2);
	else if (!input->c && !ft_strncmp((*line), "C", 1))
		input->c = ft_strdup_nonl((*line) + 2);
	else if ((*line)[0] == '1' || (*line)[0] == '0' || (*line)[0] == ' ')
		parse_input_map(line, player, map);
}

bool	parse_input(t_input *input, t_player *player, t_map *map)
{
	int		fd;
	char	*line;

	line = ft_calloc(1, sizeof(char));
	if (map->width != -1)
	{
		fd = open("maps/test", O_RDWR | O_APPEND, 0644);
		while (line)
		{
			free (line);
			line = get_next_line(fd);
			if (!line)
				break ;
			parse_line(&line, input, player, map);
		}
	}
	parse_debug(input, player, map);
	return (true);
}
