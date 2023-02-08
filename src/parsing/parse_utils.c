/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:38:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/08 01:02:34 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	error(int row, int col, t_error error)
{
	if (error == PLAYER_ERROR)
		ft_putstr_fd("Error: spawn not defined", 2);
	else if (error == PARAM_ERROR)
		ft_putstr_fd("Error: required map params not set", 2);
	else
	{
		ft_putstr_fd("Error in row: ", 2);
		ft_putnbr_fd(row + 1, 2);
		ft_putstr_fd(" col: ", 2);
		ft_putnbr_fd(col + 1, 2);
	}
	write(2, "\n", 1);
	return (false);
}

char	*ft_strdup_nonl(const char *s1)
{
	size_t		len_s1;
	size_t		i;
	char		*ptr;

	len_s1 = ft_strlen(s1);
	i = 0;
	ptr = malloc(len_s1 + 1);
	if (!ptr)
		return (NULL);
	while (i < len_s1)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[--i] = '\0';
	return (ptr);
}
