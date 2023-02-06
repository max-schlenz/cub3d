/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:35:15 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/06 14:35:29 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

int	wall_check(t_parse *map, t_movement *move, int f_b, int l_r)
{
	if (map->array[move->y + f_b][move->x + l_r] == '1')
		return (1);
	return (0);
}
