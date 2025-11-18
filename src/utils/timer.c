/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:49:23 by enogueir          #+#    #+#             */
/*   Updated: 2025/11/11 18:16:38 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	timeval_to_sec(const struct timeval *tv)
{
	return ((double)tv->tv_sec + (double)tv->tv_usec / 1000000.0);
}

double	timer_delta(void)
{
	static struct timeval	last = {0, 0};
	struct timeval			now;
	double					delta;

	gettimeofday(&now, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = now;
		return (0.0);
	}
	delta = timeval_to_sec(&now) - timeval_to_sec(&last);
	last = now;
	if (delta < 0.0)
		return (0.0);
	return (delta);
}

void	timer_sleep(double target_hz)
{
	static struct timeval	frame_start = {0, 0};
	struct timeval			now;
	double					elapsed;
	double					target;
	long					sleep_us;

	if (target_hz <= 0.0)
		return ;
	target = 1.0 / target_hz;
	gettimeofday(&now, NULL);
	if (frame_start.tv_sec == 0 && frame_start.tv_usec == 0)
	{
		frame_start = now;
		return ;
	}
	elapsed = timeval_to_sec(&now) - timeval_to_sec(&frame_start);
	if (elapsed < target)
	{
		sleep_us = (long)((target - elapsed) * 1000000.0);
		if (sleep_us > 0)
			usleep(sleep_us);
		gettimeofday(&now, NULL);
	}
	frame_start = now;
}

void	timer_log_fps(void)
{
	static struct timeval	log_start = {0, 0};
	static int				frames = 0;
	struct timeval			now;
	double					elapsed;
	double					fps;

	gettimeofday(&now, NULL);
	if (log_start.tv_sec == 0 && log_start.tv_usec == 0)
		log_start = now;
	++frames;
	elapsed = timeval_to_sec(&now) - timeval_to_sec(&log_start);
	if (elapsed < 1.0)
		return ;
	fps = frames / elapsed;
	printf("[timer] %.2f FPS (avg %.2f ms)\n", fps,
		(elapsed / frames) * 1000.0);
	log_start = now;
	frames = 0;
}
