/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:19:06 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/20 15:15:04 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	calc_req_chars(int n)
{
	int	r;

	r = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		r++;
	}
	return (r);
}

static void	create_string(char *str, int n, int i)
{
	if (n)
	{
		while (n != 0)
		{
			if (n > 0)
				str[i - 1] = n % 10 + '0';
			else
				str[i - 1] = n % 10 * (-1) + '0';
			n /= 10;
			i--;
		}
	}
	else
		str[0] = '0';
}

void	ft_itoa_stack(int n, char *str)
{
	int		digit_count;
	int		i;
	int		is_neg;

	is_neg = 0;
	if (n < 0)
	{
			n *= -1;
			is_neg = 1;
	}
	digit_count = calc_req_chars(n);
	i = digit_count + is_neg;
	create_string(str, n, i);
	if (is_neg)
		str[0] = '-';
	str[digit_count + is_neg] = '\0';
}

static void	print_fps(mlx_image_t *img, int frame_count)
{
	int		i;
	int		tmp;
	char	fps[20];

	i = 0;
	tmp = 0;
	ft_itoa_stack(frame_count, fps);
	while (fps[i])
	{
		tmp = i * 10;
		img_draw_char(img, mlx_get_texoffset(fps[i++]), (1000 * 980) + tmp);
	}
}

void	update_fps_counter(mlx_t *mlx, mlx_image_t *img)
{
	static int		old_fps = 0;
	static int		frame_count = 0;
	static double	delta = 0;

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
