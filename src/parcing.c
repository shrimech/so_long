/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrimech <shrimech@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:26:05 by shrimech          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:42 by shrimech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	elements_count(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->high)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] == 'C')
				game->colect++;
			if (game->map[i][j] == 'E')
				game->exit++;
			if (game->map[i][j] == 'P')
				game->player++;
			j++;
		}
		i++;
	}
	if (game->colect < 1 || game->exit != 1 || game->player != 1)
		return (0);
	return (1);
}

int	map_elements(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == '0' || game->map[i][j] == '1'
				|| game->map[i][j] == 'P' || game->map[i][j] == 'C'
				|| game->map[i][j] == 'E')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

size_t	gt_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	hight_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		game->high++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	check_map(char *av, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(av, O_RDONLY);
	hight_map(game, av);
	game->map = malloc(sizeof(char *) * (game->high + 1));
	line = get_next_line(fd);
	if (!line)
		return (0);
	game->width = gt_strlen(line);
	while (line)
	{
		game->map[i] = ft_strdup(line);
		free(line);
		line = NULL;
		if (gt_strlen(game->map[i]) != game->width || game->map[i][0] != '1'
			|| game->map[i][gt_strlen(game->map[i]) - 1] != '1')
			return ((free_if_i(game, i), 0));
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = NULL;
	return ((close(fd), 1));
}
