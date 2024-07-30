/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:36:34 by okoca             #+#    #+#             */
/*   Updated: 2024/07/30 13:52:44 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (av[1][0] == '\0')
		return (2);
	return (0);
}

int	check_path(char *path)
{
	int		i;
	char	*dot;

	i = 0;
	dot = ft_strchr(path, '.');
	if (!dot)
		return (2);
	if (ft_strcmp(dot, ".ber") != 0)
		return (3);
	return (0);
}

int	parsing(char *path, t_ctx *ctx)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	line = NULL;
	(void)ctx;
	if (check_path(path) != 0)
	{
		printf("check path: %d\n", check_path(path));
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (2);
	while (1)
	{
		if (i == 5)
			break ;
		// line = get_next_line();
		i++;
	}
	close(fd);
	return (0);
}
