/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:30:09 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/08 15:30:25 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	parse_debug(t_input *input, t_player *player, t_map *map)
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