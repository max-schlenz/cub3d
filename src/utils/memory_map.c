/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 02:04:44 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/12 02:05:39 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static bool	get_map_params(t_map *map)
{
	int		fd;
	int		width_line;
	char	*line;

	if (!access(MAPNAME, F_OK))
	{
		fd = open(MAPNAME, O_RDONLY);
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

char	**prep_map(t_map *map)
{
	int		i;
	char	**elem;

	i = 0;
	get_map_params(map);
	elem = ft_calloc(map->height + 2, sizeof(char *));
	if (!elem)
		return (NULL);
	while (i < map->height)
	{
		elem[i] = ft_calloc(map->width + 2, sizeof(char));
		if (!elem[i])
		{
			while (i >= 0)
				free(elem[i--]);
			free(elem);
			return (NULL);
		}
		ft_memset(elem[i++], '2', map->width + 1);
	}
	elem[map->height + 1] = NULL;
	return (elem);
}
