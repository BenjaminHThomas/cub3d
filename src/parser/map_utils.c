/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:29:11 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 20:05:18 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_input(t_map_data *mapdata)
{
	size_t	i;

	i = -1;
	while (mapdata->input[++i])
		printf("%s", mapdata->input[i]);
}

int	get_max_line_len(t_map_data *mapdata)
{
	(void)mapdata;
	return (0);
}
