/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_used_funtions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 06:33:15 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/20 14:02:15 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	matrix_two(double *array, double degree)
{
	double	x;
	double	y;

	x = array[0] * cos(degree) - array[1] * sin(degree);
	y = array[0] * sin(degree) + array[1] * cos(degree);
	array[0] = x;
	array[1] = y;
}

