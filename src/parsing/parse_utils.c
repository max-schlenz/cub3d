/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:38:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/18 14:23:15 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	error(int row, int col, t_error error)
{
	char	*error_msg[4];

	if (error == UNEXPECTED_ERROR)
	{
		ft_putstr_fd("Error in row: ", STDERR_FILENO);
		ft_putnbr_fd(row + 1, STDERR_FILENO);
		ft_putstr_fd(" col: ", STDERR_FILENO);
		ft_putnbr_fd(col + 1, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		error_msg[TEXTURE_ERROR] = "Error: loading textures failed";
		error_msg[MAP_ERROR] = "Error: invalid map";
		error_msg[PARAM_ERROR] = "Error: required map params not set";
		error_msg[PLAYER_ERROR] = "Error: spawn not set";
		ft_putendl_fd(error_msg[error], STDERR_FILENO);
	}
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
