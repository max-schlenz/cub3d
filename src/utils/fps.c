/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:19:06 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/18 12:19:20 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	print_fps(mlx_image_t *img, int frame_count)
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
