/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:26:45 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/11/03 18:59:21 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_map_directory(t_game *g, const char *path)
{
	const char	*slash;

	if (!g || !path)
		return (0);
	slash = ft_strrchr(path, '/');
	free(g->map_dir);
	g->map_dir = NULL;
	if (!slash)
	{
		g->map_dir = ft_strdup(".");
		return (g->map_dir != NULL);
	}
	if (slash == path)
	{
		g->map_dir = ft_strdup("/");
		return (g->map_dir != NULL);
	}
	g->map_dir = ft_substr(path, 0, (size_t)(slash - path));
	return (g->map_dir != NULL);
}
