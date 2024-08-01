/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:45:55 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 13:42:26 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_space(unsigned char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line && line[i])
	{
		if (!is_space(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

int	resize_arr(char ***arr, int *size)
{
	char	**new_arr;
	size_t	arrlen;

	if (!arr || !*arr)
		return (1);
	*size = (*size) * 2;
	new_arr = (char **)ft_calloc(sizeof(char *), (*size) + 1);
	if (!new_arr)
		return (1);
	arrlen = 0;
	while ((*arr)[arrlen])
		arrlen++;
	new_arr = ft_memmove(new_arr, *arr, arrlen);
	free_arr(*arr);
	*arr = new_arr;
	return (0);
}
