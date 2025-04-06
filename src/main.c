/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrimech <shrimech@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:10:31 by shrimech          #+#    #+#             */
/*   Updated: 2025/04/06 18:11:27 by shrimech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_exit(t_game *game)
{
	exit((free_game_map(game), free_textures(game), pause_mlx(game), 1));
	return (0);
}

void	my_x_gestion(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit((write(2, "no x server", 11), 1));
	texture(game);
	game->mlx_win = mlx_new_window(game->mlx, game->width * 32, game->high * 32,
			"so_long");
	render_map(game);
	mlx_key_hook(game->mlx_win, key_hook, game);
	mlx_hook(game->mlx_win, 17, 0, ft_exit, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;
	char	*ext;

	ext = ft_strrchr(av[1], '.');
	if (ac == 2)
	{
		if (!ext || ft_strncmp(ext, ".ber", 4) != 0 || ext == av[1] || *(ext
				- 1) == '/')
			return ((write(2, "Error: file must be <name>.ber\n", 31), 1));
		game_init(&game);
		if (check_map(av[1], &game) == 0)
			return ((write(2, "ERROR : invalid map\n", 20), 1));
		if (map_elements(&game) == 0 || elements_count(&game) == 0
			|| check_oporunity_to_col_exit(&game) == 0)
			return ((free_game_map(&game), write(2, "ERROR:invalid map\n", 18),
					1));
		my_x_gestion(&game);
	}
	else
		return (write(1, "Error: enter <./so_long> <map.ber>", 34), 1);
}
// okok