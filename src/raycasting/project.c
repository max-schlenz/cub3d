/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:19:38 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/15 17:01:51 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// void render_ceiling_floor(mlx_t *mlx, mlx_image_t *img, t_movement *move, t_map *map, t_texture *tex)
// {
	
// }
void draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_memset_cub(int *b, uint32_t c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		draw_pixel((uint8_t *)&b[i], c);
		i++;
	}
	return ;
}

void project(mlx_t *mlx, mlx_image_t *img_bg, t_movement *move, t_map *map, t_texture *tex)
{
	// ft_memset_cub((int *)img_bg->pixels, MLX_COLOR_GRAY, (img_bg->width * img_bg->height / 2));
	ft_memset_cub((int *)img_bg->pixels, map->color_ceiling, img_bg->width * img_bg->height / 2);
	ft_memset_cub((int *)img_bg->pixels + (img_bg->width * img_bg->height) / 2, map->color_floor, img_bg->width * img_bg->height / 2);
	mlx_image_to_window(mlx, img_bg, 0, 0);
}
