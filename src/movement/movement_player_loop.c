/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-18 17:10:59 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-11-18 17:10:59 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	accumulate_movement(t_game *g, double speed, double *dx, double *dy)
{
	if (g->keys.w)
	{
		*dx += g->player.dir.x * speed;
		*dy += g->player.dir.y * speed;
	}
	if (g->keys.s)
	{
		*dx -= g->player.dir.x * speed;
		*dy -= g->player.dir.y * speed;
	}
	if (g->keys.a)
	{
		*dx += -g->player.dir.y * speed;
		*dy += g->player.dir.x * speed;
	}
	if (g->keys.d)
	{
		*dx += g->player.dir.y * speed;
		*dy += -g->player.dir.x * speed;
	}
}

void	handle_move(t_game *g)
{
	double	speed;
	double	dx;
	double	dy;

	speed = MOVE_SPEED;
	dx = 0.0;
	dy = 0.0;
	accumulate_movement(g, speed, &dx, &dy);
	update_position(g, dx, dy);
}
