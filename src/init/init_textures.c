/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:54:47 by enogueir          #+#    #+#             */
/*   Updated: 2025/11/11 20:43:35 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static const char	*resolve_texture_path(t_game *g, const char *path,
	char **to_free)
{
	char	*candidate;

	*to_free = NULL;
	if (can_open_readonly(path))
		return (path);
	if (!g->map_dir || path[0] == '\0' || path[0] == '/')
		return (NULL);
	candidate = join_texture_path(g->map_dir, path);
	if (!candidate)
		return (NULL);
	if (!can_open_readonly(candidate))
	{
		free(candidate);
		return (NULL);
	}
	*to_free = candidate;
	return (candidate);
}

int	load_texture_with_base(t_game *g, t_texture *tex, const char *path)
{
	const char	*source;
	char		*to_free;
	int			result;

	if (!path || !*path)
		return (err("Missing texture path"));
	source = resolve_texture_path(g, path, &to_free);
	if (!source)
		return (err("Cannot open texture file"));
	result = load_texture(g->mlx, tex, source);
	if (to_free)
		free(to_free);
	return (result);
}

int	init_textures(t_game *g)
{
	if (!g || !g->mlx)
		return (err("MLX not initialized"));
	if (!load_texture_with_base(g, &g->no, g->no_texture))
		return (0);
	if (!load_texture_with_base(g, &g->so, g->so_texture))
		return (0);
	if (!load_texture_with_base(g, &g->we, g->we_texture))
		return (0);
	if (!load_texture_with_base(g, &g->ea, g->ea_texture))
		return (0);
	return (1);
}
