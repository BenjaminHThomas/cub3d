/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:45:55 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/03 09:56:36 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	array_len(void	**arr)
{
	size_t	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

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
	size_t	i;

	if (!arr || !*arr)
		return (1);
	*size = (*size) * 2;
	new_arr = (char **)ft_calloc(sizeof(char *), (*size) + 1);
	if (!new_arr)
		return (1);
	arrlen = array_len((void **)(*arr));
	i = 0;
	while (i < arrlen)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = new_arr;
	return (0);
}

unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}
