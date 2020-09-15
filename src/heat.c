/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:39:16 by rlintill          #+#    #+#             */
/*   Updated: 2020/09/15 15:35:23 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		get_dist(t_filler *filler, int y, int x)
{
	int		min_dist;
	int		dist;
	int		i;
	int		j;

	i = 0;
	dist = 0;
	min_dist = 2147483647;
	while (i < filler->map->height)
	{
		j = 0;
		while (j < filler->map->width)
		{
			if (filler->map->fig[i][j] == filler->opponent
				|| filler->map->fig[i][j] == (filler->opponent + 32))
			{
				dist = mod(y - i) + mod(x - j);
				if (dist < min_dist)
					min_dist = dist;
			}
			j++;
		}
		i++;
	}
	return (min_dist);
}

void	set_heat_map(t_filler *f)
{
	int		i;
	int		j;

	f->heat->height = f->map->height;
	f->heat->width = f->map->width;
	if (!(f->heat->fig = (int **)malloc(sizeof(int *) * (f->heat->height + 1))))
		exit(1);
	i = 0;
	while (i < f->heat->height)
	{
		j = 0;
		if (!(f->heat->fig[i] = (int *)malloc(sizeof(int) * (f->heat->width + 1))))
			exit(1);
		while (j < f->heat->width)
		{
			if (f->map->fig[i][j] == f->me
				|| f->map->fig[i][j] == (f->me + 32))
				f->heat->fig[i][j] = -1;
			else if (f->map->fig[i][j] == f->opponent
				|| f->map->fig[i][j] == (f->opponent + 32))
				f->heat->fig[i][j] = 0;
			else
				f->heat->fig[i][j] = get_dist(f, i, j);
			j++;
		}
		i++;
	}
	f->heat->fig[i] = NULL;
}

void	rew_heat_map(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	while (i < filler->heat->height)
	{
		j = 0;
		while (j < filler->heat->width)
		{
			if (filler->map->fig[i][j] == filler->me
				|| filler->map->fig[i][j] == (filler->me + 32))
				filler->heat->fig[i][j] = -1;
			else if (filler->map->fig[i][j] == filler->opponent
				|| filler->map->fig[i][j] == (filler->opponent + 32))
				filler->heat->fig[i][j] = 0;
			else
				filler->heat->fig[i][j] = get_dist(filler, i, j);
			j++;
		}
		i++;
	}
}