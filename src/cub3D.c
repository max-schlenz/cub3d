/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 16:05:36 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	parse_cleanup(t_parse *parse)
{
	free_null(6, &parse->tex_no, &parse->tex_so, &parse->tex_we, &parse->tex_ea,
		&parse->f, &parse->c);
	free_array(parse->array);
	free(parse);
}

static t_parse *parse_init()
{
	t_parse	*parse;
	
	parse = ft_calloc(1, sizeof(t_parse));
	parse->tex_no = NULL;
	parse->tex_so = NULL;
	parse->tex_we = NULL;
	parse->tex_ea = NULL;
	parse->f = NULL;
	parse->c = NULL;
	parse->player_x = 0;
	parse->player_y = 0;
	parse->player_dir = 0;
	return (parse);
}

int	main(void)
{
	t_parse *parse;
	
	parse = parse_init();
	parse_map(parse);
	if (is_map_valid(parse))
		main_casting(parse);
	else
		printf("Invalid map\n");
	parse_cleanup(parse);
	return (0);
}