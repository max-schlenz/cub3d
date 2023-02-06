/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:17:57 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 16:05:03 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static bool	get_map_size(t_parse *parse)
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
		parse->map_width = width;
		parse->map_height = height;
		return (true);
	}
	return (false);
}

static void	allocate_map_arr(t_parse *parse)
{
	int **arr;

	parse->array = ft_calloc(parse->map_height + 2, sizeof(char*));
	for (int i = 0; i < parse->map_height; i++)
	{
		parse->array[i] = ft_calloc(parse->map_width + 2, sizeof(char));
		ft_memset(parse->array[i], '2', parse->map_width + 1);
	}
	parse->array[parse->map_height + 1] = NULL;
}

bool is_map_valid(t_parse *parse)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!parse->player_dir)
	{
		printf("Found error in row: %i col: %i\n", i + 1, j + 1);
		exit(1);
	}
		
	while (i < parse->map_height)
	{
		while (j < parse->map_width)
		{
			if (parse->array[i][j] == '0') 
			{
				if (i == 0 || j == 0 || i == parse->map_height - 1
					|| j == parse->map_width - 1
					|| !parse->array[i][j + 1]
					|| parse->array[i - 1][j] == '2'	//check up
					|| parse->array[i][j - 1] == '2'	//		left
					|| parse->array[i + 1][j] == '2'	//		down
					|| parse->array[i][j + 1] == '2')	//		right
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

void	parse_map(t_parse *parse)
{
	get_map_size(parse);
	allocate_map_arr(parse);

	int		fd;
	int		line;
	char	*read_buf;
	
	line = 0;
	int i = 0;
	if (parse->map_width != -1)
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		read_buf = ft_strdup("42");
		while (line < parse->map_height)
		{
			free_null(1, &read_buf);
			read_buf = get_next_line(fd);
			if (read_buf && read_buf[0] == '\n')
				continue ;
			if (!ft_strncmp(read_buf, "NO", 2))
			{
				parse->tex_no = ft_strdup_nonl(read_buf + 3);
				continue;
			}
			else if (!ft_strncmp(read_buf, "SO", 2))
			{
				parse->tex_so = ft_strdup_nonl(read_buf + 3);	
				continue;
			}
			else if (!ft_strncmp(read_buf, "WE", 2))
			{
				parse->tex_we = ft_strdup_nonl(read_buf + 3);	
				continue;
			}
			else if (!ft_strncmp(read_buf, "EA", 2))
			{
				parse->tex_ea = ft_strdup_nonl(read_buf + 3);
				continue;
			}
			else if (!ft_strncmp(read_buf, "F ", 2))
			{
				parse->f = ft_strdup_nonl(read_buf + 2);
				continue;
			}
			else if (!ft_strncmp(read_buf, "C ", 2))
			{
				parse->c = ft_strdup_nonl(read_buf + 2);
				continue;
			}
			i = 0;
			while (read_buf && read_buf[i] && read_buf[i] != '\n')
			{
				if (line < parse->map_height)
				{
					if (read_buf[i] == 'N' || read_buf[i] == 'S' || read_buf[i] == 'W' || read_buf[i] == 'E')
					{
						if (parse->player_dir != 0)
						{
							printf("Error: multiple player spawns (line: %i, row: %i)\n", line, i);
							exit (0);
						}
						parse->player_x = i;
						parse->player_y = line;
						parse->player_dir = read_buf[i];
					}
					if (read_buf[i] == ' ')
						read_buf[i] = '2';
					parse->array[line][i] = read_buf[i];
				}
				i++;
				parse->array[line][i] = '2';
			}
			line++;
		}
		free_null(1, &read_buf);
	}
	
	if (!parse->tex_no
	||	!parse->tex_so
	||	!parse->tex_we
	||	!parse->tex_ea
	||	!parse->f
	||	!parse->c)
	{
		printf("Error: required map params not set.\n");
		exit(0);
	}
	
	for (int i = 0; i < parse->map_height; i++)
	{
		for (int j = 0; j < parse->map_width; j++)
			printf("%c", parse->array[i][j]);
		printf("\n");
	}

	printf("\nWIDTH: %i, HEIGHT: %i\n", parse->map_width, parse->map_height);
	printf("tex_no: %s\n", parse->tex_no);
	printf("tex_so: %s\n", parse->tex_so);
	printf("tex_we: %s\n", parse->tex_we);
	printf("tex_ea: %s\n", parse->tex_ea);
	printf("f: %s\n", parse->f);
	printf("c: %s\n", parse->c);
	printf("player_x: %i\n", parse->player_x);
	printf("player_y: %i\n", parse->player_y);
	printf("player_dir: %c\n", parse->player_dir);
}
