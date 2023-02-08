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
	
	if (!access("test", F_OK))
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		if (!fd)
			return (false);
		line = ft_strdup("42");
		while (line != NULL)
		{
			free (line);
			line = get_next_line(fd);
			if (line && (line[0] == '\n' || (line[0] != '0' && line[0] != '1' && line[0] != ' ')))
				continue;
			if (line)
				map->height++;
			width_line = ft_strlen(line) - 1;
			if (width_line > map->width)
				map->width = width_line;
		}
		return (true);
	}
	return (false);
}

static char	**alloc_map(t_map *map)
{
	int		i;
	char	**elem;

	i = 0;
	elem = ft_calloc(map->height + 2, sizeof(char*));
	while (i < map->height)
	{
		elem[i] = ft_calloc(map->width + 2, sizeof(char));
		ft_memset(elem[i++], '2', map->width + 1);
	}
	elem[map->height + 1] = NULL;
	return (elem);
}

bool input_valid(t_input *input, t_player *player, t_map *map)
{
	int row;
	int col;

	row = 0;
	col = 0;
	if (!player->player_dir)
		return (error(row, col, PLAYER_ERROR));
	while (row < map->height && col < map->width)
	{
		if (map->elem[row][col] == '0')
		{
			if (row == 0 || col == 0 || row == map->height - 1
				|| col == map->width - 1 || !map->elem[row][col + 1]
				|| map->elem[row - 1][col] == '2'
				|| map->elem[row][col - 1] == '2'
				|| map->elem[row + 1][col] == '2'
				|| map->elem[row][col + 1] == '2')
					return (error(row, col, MAP_ERROR));
		}
		if (++col == map->width)
		{
			col = 0;
			row++;
		}
	}
	return (true);
}

static void parse_input_map(char **read_buf, t_player *player, t_map *map, int *line)
{
	int	i;

	i = 0;
	while ((*read_buf) && (*read_buf)[i] && (*read_buf)[i] != '\n')
	{
		if ((*line) < map->height)
		{
			if ((*read_buf)[i] == 'N' || (*read_buf)[i] == 'S' || (*read_buf)[i] == 'W' || (*read_buf)[i] == 'E')
			{
				if (player->player_dir != 0)
				{
					printf("Error: multiple player spawns (line: %i, row: %i)\n", (*line), i);
					exit (0);
				}
				player->player_x = i;
				player->player_y = (*line);
				player->player_dir = (*read_buf)[i];
			}
			if ((*read_buf)[i] == ' ')
				(*read_buf)[i] = '2';
			map->elem[(*line)][i] = (*read_buf)[i];
		}
		i++;
	}
	(*line)++;
}


bool	parse_input(t_input *input, t_player *player, t_map *map)
{
	int		fd;
	int		line;
	char	*read_buf;
	
	get_map_params(map);
	map->elem = alloc_map(map);
	read_buf = ft_calloc(1, sizeof(char));
	int i = 0;
	if (map->width != -1)
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		while (i < map->height)
		{
			free (read_buf);
			read_buf = get_next_line(fd);
			if (!read_buf)
				break ;
			else if (!input->tex_no && !ft_strncmp(read_buf, "NO", 2))
				input->tex_no = ft_strdup_nonl(read_buf + 3);
			else if (!input->tex_so && !ft_strncmp(read_buf, "SO", 2))
				input->tex_so = ft_strdup_nonl(read_buf + 3);
			else if (!input->tex_we && !ft_strncmp(read_buf, "WE", 2))
				input->tex_we = ft_strdup_nonl(read_buf + 3);
			else if (!input->tex_ea && !ft_strncmp(read_buf, "EA", 2))
				input->tex_ea = ft_strdup_nonl(read_buf + 3);
			else if (!input->f && !ft_strncmp(read_buf, "F ", 2))
				input->f = ft_strdup_nonl(read_buf + 2);
			else if (!input->c && !ft_strncmp(read_buf, "C ", 2))
				input->c = ft_strdup_nonl(read_buf + 2);
			else if (read_buf && (read_buf[0] == '\n' || (read_buf[0] != '0' && read_buf[0] != '1' && read_buf[0] != ' ')))
				continue;
			else
				parse_input_map(&read_buf, player, map, &i);
		}
		free (read_buf);
	}

	if (!input->tex_no || !input->tex_so || !input->tex_we || !input->tex_ea
		|| !input->f || !input->c)
		return (error(0, 0, PARAM_ERROR));
	
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
