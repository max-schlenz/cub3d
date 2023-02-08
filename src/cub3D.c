/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:18:12 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/07 13:44:00 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	textures_cleanup(t_texture *textures)
{
	mlx_delete_texture(textures->wall_no);
	mlx_delete_texture(textures->wall_so);
	mlx_delete_texture(textures->wall_we);
	mlx_delete_texture(textures->wall_ea);
	mlx_delete_texture(textures->player);
	free(textures);
}

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

static t_texture	*load_textures(t_parse *parse)
{
	t_texture	*textures;

	textures = ft_calloc(1, sizeof(t_texture));
	textures->wall_no = mlx_load_png(parse->tex_no);
	textures->wall_so = mlx_load_png(parse->tex_so);
	textures->wall_we = mlx_load_png(parse->tex_we);
	textures->wall_ea = mlx_load_png(parse->tex_ea);
	textures->player = mlx_load_png("res/player.png");

	return (textures);
}

int	main(void)
{
	t_parse		*parse;
	t_texture	*textures;
	
	parse = parse_init();
	parse_map(parse);
	if (is_map_valid(parse))
	{
		textures = load_textures(parse);
		main_casting(parse, textures);
	}
	else
		printf("Invalid map\n");
	parse_cleanup(parse);
	textures_cleanup(textures);
	return (0);
}