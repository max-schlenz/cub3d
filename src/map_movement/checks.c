/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:35:15 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/02/15 18:42:18 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<cub3D.h>

int	wall_check(t_map *map, t_movement *move, int f_b, int l_r)
{
	if (map->elem[move->y + f_b][move->x + l_r] == '1'
		|| map->elem[move->y + f_b][move->x + l_r] == 'D')
		return (1);
	return (0);
}
