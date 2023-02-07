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
	int		width;
	int		width_tmp;
	int		height;
	char	*read_buf;
	
	width = 0;
	height = 0;
	width_tmp = 0;
	if (!access("test", F_OK))
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		if (!fd || access("test", F_OK))
			return (false);
		read_buf = ft_strdup("42");
		while (read_buf != NULL)
		{
			free_null(1, &read_buf);
			read_buf = get_next_line(fd);
			if (read_buf && read_buf[0] && read_buf[0] != '0' && read_buf[0] != '1' && read_buf[0] != ' ')
				continue;
			if (read_buf && read_buf[0] == '\n')
				continue ;
			if (read_buf)
				height++;
			width_tmp = ft_strlen(read_buf) - 1;
			if (width_tmp > width)
				width = width_tmp;
		}
		map->width = width;
		map->height = height;
		return (true);
	}
	return (false);
}

static char	**alloc_map(t_map *map)
{
	char **elem;

	elem = ft_calloc(map->height + 2, sizeof(char*));
	for (int i = 0; i < map->height; i++)
	{
		elem[i] = ft_calloc(map->width + 2, sizeof(char));
		ft_memset(elem[i], '2', map->width + 1);
	}
	elem[map->height + 1] = NULL;

	return (elem);
}

bool input_valid(t_input *input, t_player *player, t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!player->player_dir)
	{
		printf("Found error in row: %i col: %i\n", i + 1, j + 1);
		exit(1);
	}
		
	while (i < map->height)
	{
		while (j < map->width)
		{
			if (map->elem[i][j] == '0') 
			{
				if (i == 0 || j == 0 || i == map->height - 1
					|| j == map->width - 1
					|| !map->elem[i][j + 1]
					|| map->elem[i - 1][j] == '2'	//check up
					|| map->elem[i][j - 1] == '2'	//		left
					|| map->elem[i + 1][j] == '2'	//		down
					|| map->elem[i][j + 1] == '2')	//		right
					{
						printf("Found error in row: %i col: %i\n", i + 1, j + 1);
						return (false);
					}
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (true);
}

void	parse_input(t_input *input, t_player *player, t_map *map)
{
	int		fd;
	int		line;
	char	*read_buf;
	
	get_map_params(map);
	map->elem = alloc_map(map);
	line = 0;
	int i = 0;
	if (map->width != -1)
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		read_buf = ft_strdup("42");
		while (line < map->height)
		{
			free_null(1, &read_buf);
			read_buf = get_next_line(fd);
			if (read_buf && read_buf[0] == '\n')
				continue ;
			if (read_buf)
			{
				if (!ft_strncmp(read_buf, "NO", 2))
				{
					input->tex_no = ft_strdup_nonl(read_buf + 3);
					continue;
				}
				else if (!ft_strncmp(read_buf, "SO", 2))
				{
					input->tex_so = ft_strdup_nonl(read_buf + 3);	
					continue;
				}
				else if (!ft_strncmp(read_buf, "WE", 2))
				{
					input->tex_we = ft_strdup_nonl(read_buf + 3);	
					continue;
				}
				else if (!ft_strncmp(read_buf, "EA", 2))
				{
					input->tex_ea = ft_strdup_nonl(read_buf + 3);
					continue;
				}
				else if (!ft_strncmp(read_buf, "F ", 2))
				{
					input->f = ft_strdup_nonl(read_buf + 2);
					continue;
				}
				else if (!ft_strncmp(read_buf, "C ", 2))
				{
					input->c = ft_strdup_nonl(read_buf + 2);
					continue;
				}
			}
			i = 0;
			while (read_buf && read_buf[i] && read_buf[i] != '\n')
			{
				if (line < map->height)
				{
					if (read_buf[i] == 'N' || read_buf[i] == 'S' || read_buf[i] == 'W' || read_buf[i] == 'E')
					{
						if (player->player_dir != 0)
						{
							printf("Error: multiple player spawns (line: %i, row: %i)\n", line, i);
							exit (0);
						}
						player->player_x = i;
						player->player_y = line;
						player->player_dir = read_buf[i];
					}
					if (read_buf[i] == ' ')
						read_buf[i] = '2';
					map->elem[line][i] = read_buf[i];
				}
				i++;
				map->elem[line][i] = '2';
			}
			line++;
		}
		free_null(1, &read_buf);
	}
	
	if (!input->tex_no
	||	!input->tex_so
	||	!input->tex_we
	||	!input->tex_ea
	||	!input->f
	||	!input->c)
	{
		printf("Error: required map params not set.\n");
		exit(0);
	}
	
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
