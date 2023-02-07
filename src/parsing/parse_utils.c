/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:38:03 by mschlenz          #+#    #+#             */
/*   Updated: 2023/02/06 15:38:17 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
