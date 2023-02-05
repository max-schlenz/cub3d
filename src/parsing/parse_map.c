/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:17:57 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/05 14:43:53 by mschlenz         ###   ########.fr       */
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
			if (read_buf && read_buf[0] == '\n')
				continue ;
			height++;
			width_tmp = ft_strlen(read_buf);
			if (width_tmp > width)
				width = width_tmp;
		}
		parse->map_width = width - 1;
		parse->map_height = height - 1;
		return (true);
	}
	return (false);
}

static void	allocate_map_arr(t_parse *parse)
{
	int **arr;

	parse->array = ft_calloc(parse->map_height, sizeof(char*));
	for (int i = 0; i < parse->map_height; i++)
	{
		parse->array[i] = ft_calloc(parse->map_width + 2, sizeof(char));
		ft_memset(parse->array[i], '2', parse->map_width + 1);
	}
}

bool is_map_valid(t_parse *parse)
{
	int i;
	int j;

	i = 0;
	j = 0;
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
			i = 0;
			for (; read_buf && read_buf[i] && read_buf[i] != '\n'; i++)
			{
				if (read_buf[i] == ' ')
					read_buf[i] = '2';
				parse->array[line][i] = read_buf[i];
			}
			parse->array[line][i] = '2';
			line++;
		}
	}
	
	
	for (int i = 0; i < parse->map_height; i++)
	{
		for (int j = 0; j < parse->map_width; j++)
			printf("%c", parse->array[i][j]);
		printf("\n");
	}
	
	printf("\nWIDTH: %i, HEIGHT: %i\n", parse->map_width, parse->map_height);
}
