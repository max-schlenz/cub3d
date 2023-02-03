/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/03 15:39:23 by lkrabbe          ###   ########.fr       */
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
	
	parse->array = ft_calloc(parse->map_height, sizeof(int*));
	for (int i = 0; i < parse->map_height; i++)
	{
		parse->array[i] = malloc(parse->map_width * sizeof(int));
		ft_memset(parse->array[i], '2', parse->map_width);
	}
}

static void	parse_map(t_parse *parse)
{
	get_map_size(parse);
	allocate_map_arr(parse);
	printf("WIDTH: %i, HEIGHT: %i\n", parse->map_width, parse->map_height);

	int		fd;
	int		line;
	char	*read_buf;
	
	line = 0;
	if (parse->map_width != -1)
	{
		fd = open("test", O_RDWR | O_APPEND, 0644);
		read_buf = ft_strdup("42");
		while (read_buf != NULL)
		{
			free_null(1, &read_buf);
			read_buf = get_next_line(fd);
			if (read_buf && read_buf[0] == '\n')
				continue ;
			for (int i = 0; read_buf && read_buf[i] && read_buf[i] != '\n'; i++)
			{
				if (read_buf[i] == ' ')
					read_buf[i] = '2';
				parse->array[line][i] = read_buf[i];
			}
			line++;
		}
	}
	
	for (int i = 0; i < parse->map_height; i++)
	{
		for (int j = 0; j < parse->map_width; j++)
			printf("%c", parse->array[i][j]);
		printf("\n");
	}
}


int	main(void)
{
	t_parse	*parse = ft_calloc(1, sizeof(t_parse));
	parse_map(parse);
	main_casting(parse);
}