/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:35:06 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 14:21:43 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include "../MLX42/src/font/font.h"

bool	color_count_elems(char *str_input)
{
	int	elems;
	int	i;

	elems = 0;
	i = 0;
	while (str_input[i])
	{
		if (str_input[i] == ',' && str_input[i + 1])
			elems++;
		i++;
	}
	if (elems == 2)
		return (true);
	return (false);
}

bool	check_color(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i] && (ft_isdigit(str[i]) || str[i] == ',' || str[i] == ' '))
		i++;
	if (!str[i])
		return (true);
	return (false);
}

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
