/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:35:06 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/16 13:00:57 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include "../MLX42/src/font/font.h"

// bool	check_pixel(uint8_t *start)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (*start + i == 0)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// void	put_pixel(mlx_image_t *img, double x_p, double y_p, mlx_texture_t *tex)
// {
// 	uint8_t *ptr;
// 	int	x;
// 	int	y;

// 	x = (int)(x_p * tex->width);
// 	y = (int)(y_p * tex->height) * (tex->width);
// 	ptr = &img->pixels[(int)(x * 4 + y * 4)];
// 	if (check_pixel(ptr))
// 		mlx_put_pixel(img, x, y, img_pixel(ptr));
// 	return ;
// }

void	check_inputfile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	img_draw_char(mlx_image_t *image, int32_t texoffset, int32_t imgoffset)
{
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	uint32_t	y;

	y = 0;
	if (texoffset < 0)
		return ;
	while (y < 20)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width + texoffset)
			* sizeof(int32_t)];
		pixeli = image->pixels + ((y * image->width + imgoffset)
				* sizeof(int32_t));
		ft_memcpy(pixeli, pixelx, 10 * sizeof(int32_t));
		y++;
	}
}

void	print_fps(mlx_image_t *img, int frame_count)
{
	int		i;
	int		tmp;
	char	*fps;

	i = 0;
	tmp = 0;
	fps = ft_itoa(frame_count);
	while (fps[i])
	{
		tmp = i * 10;
		img_draw_char(img, mlx_get_texoffset(fps[i++]), (1000 * 980) + tmp);
	}
}

void	update_fps_counter(mlx_t *mlx, mlx_image_t *img)
{
	int				i;
	static int		old_fps = 0;
	static int		frame_count = 0;
	static double	delta = 0;

	i = 0;
	delta += mlx->delta_time;
	frame_count++;
	if (delta >= 1.0)
	{
		old_fps = frame_count;
		print_fps(img, frame_count);
		delta = 0;
		frame_count = 0;
	}
	else if (old_fps != 0)
		print_fps(img, old_fps);
}