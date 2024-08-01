/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:05:13 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 12:10:37 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_arr(void **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	bin_textures(t_texture **texts)
{
	size_t	i;

	if (!texts)
		return ;
	i = 0;
	while (texts[i])
	{
		if (texts[i]->path)
		{
			free(texts[i]->path);
			texts[i]->path = NULL;
		}
		free(texts[i]);
		texts[i] = NULL;
		i++;
	}
	free(texts);
	texts = NULL;
	return ;
}
