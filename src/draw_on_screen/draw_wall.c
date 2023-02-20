/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 06:38:55 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/20 14:27:25 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

int	get_color(uint8_t *start)
{
	int	color;
	int	i;

	i = 0;
	color = 0;
	while (i < 4)
	{
		color = color << 8;
		color = color | *(start + i);
		i++;
	}
	return (color);
}

int	img_pixel(double x_p, double y_p, mlx_texture_t *tex)
{
	uint8_t	*ptr;
	int		x;
	int		y;

	x = (int)(x_p * tex->width);
	y = (int)(y_p * tex->height) * (tex->width);
	ptr = &tex->pixels[(int)(x * 4 + y * 4)];
	return (get_color(ptr));
}

void	draw_wall(t_array *test, mlx_image_t *img, double fov)
{
	int			skyline;
	int			wall_height;
	int			i;
	int			color;

	i = 0;
	skyline = img->height / 2;
	wall_height = DEFAULT_WALL_HEIGHT \
	/ test->distance * (img->width / 2) * tan(fov / 2);
	while (i < wall_height)
	{
		if (skyline - wall_height / 2 + i < 0)
			i = wall_height / 2 - skyline;
		if (skyline - wall_height / 2 + i > (int)img->height)
			break ;
		if (skyline - wall_height / 2 + i > 0 && \
		skyline - wall_height / 2 + i < (int)img->height)
		{
			color = img_pixel(test->tile_x, ((double)i / (double)wall_height), \
			test->texture);
			mlx_put_pixel(img, test->x, (skyline - wall_height / 2) + i, color);
		}
		i++;
	}
}
