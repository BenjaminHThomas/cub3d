/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:29:11 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 14:07:52 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Checks whether all characters in a string are the provided char */
bool	all_are_c(unsigned char c, char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		if (s[i++] != c)
			return (false);
	return (true);
}

bool	in(unsigned char c, char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	print_input(t_map_data *mapdata)
{
	size_t	i;

	i = -1;
	while (mapdata->input[++i])
		printf("%s", mapdata->input[i]);
}

size_t	get_max_map_len(t_map_data *mapdata)
{
	size_t	max_len;
	size_t	cur_len;
	size_t	i;

	max_len = 0;
	i = 6;
	while (mapdata->input[i])
	{
		cur_len = ft_strlen(mapdata->input[i]);
		if (cur_len > max_len)
			max_len = cur_len;
		i++;
	}
	return (max_len);
}

t_direction char_to_dir(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'E')
		return (EAST);
	return (WEST);
}
