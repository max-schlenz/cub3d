/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:29:23 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 13:55:50 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <cub3D.h>

typedef struct s_parse
{
	int		map_width;
	int		map_height;
	char	**array;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	*f;
	char	*c;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_parse;


#endif