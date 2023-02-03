/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrepl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:39:16 by mschlenz          #+#    #+#             */
/*   Updated: 2022/11/28 15:34:30 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

char	*strrepl(char *str, char *needle, char *repl)
{
	size_t	i;
	size_t	len_str;
	size_t	len_needle;
	size_t	len_repl;
	char	*before;
	char	*mid;
	char	*after;
	char	*ret;

	i = 0;
	before = NULL;
	after = NULL;
	mid = ft_strdup(repl);
	len_str = ft_strlen(str);
	len_needle = ft_strlen(needle);
	len_repl = ft_strlen(repl);
	while (i < len_str - len_needle)
	{
		if (!ft_strncmp(str + i, needle, len_needle))
		{
			before = ft_substr(str, 0, i);
			after = ft_strdup(str + i + len_needle);
			str = merge_str(3, before, mid, after);
			i += len_repl;
			continue ;
		}
		i++;
	}
	ret = str;
	return (ret);
}

// int main(void)
// {
// 	char		*str;

// 	str = ft_strdup("AlphaBetaGammaDeltaBetaYpsilon");
// 	printf("%s\n", strrepl(str, "Beta", "AlphaBeta"));
// 	exit(0);
// }
