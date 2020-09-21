/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 11:39:16 by rlintill          #+#    #+#             */
/*   Updated: 2020/09/15 15:35:23 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_player_info(t_filler *filler)
{
	char	*line;

	get_next_line(0, &line);
	if (line[10] == '1')
	{
		filler->me = 'O';
		filler->opponent = 'X';
	}
	else
	{
		filler->me = 'X';
		filler->opponent = 'O';
	}
	free(line);
}

void	set_map(t_obj *map)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	map->height = ft_atoi(&line[7]);
	map->width = ft_atoi(&line[7 + length_num(map->height)]);
	free(line);
	get_next_line(0, &line);
	free(line);
	i = 0;
	if (!(map->fig = (char **)malloc(sizeof(char *) * (map->height + 1))))
		exit(1);
	i = 0;
	while (i < map->height)
	{
		get_next_line(0, &line);
		map->fig[i] = ft_strdup(&line[4]);
		free(line);
		i++;
	}
}

void	rew_map(t_obj *map)
{
	char	*line;
	int		i;
	int		j;

	get_next_line(0, &line);
	free(line);
	i = 0;
	j = 0;
	while (i < map->height)
	{
		get_next_line(0, &line);
		j = 0;
		while (j < map->width)
		{
			map->fig[i][j] = line[j + 4];
			j++;
		}
		free(line);
		i++;
	}
}

void	set_filler(t_filler *filler)
{
	bzero(filler, sizeof(t_filler));
	if (!(filler->map = (t_obj*)ft_memalloc(sizeof(t_obj))))
		exit(1);
	bzero(filler->map, sizeof(t_obj));
	if (!(filler->piece = (t_obj*)ft_memalloc(sizeof(t_obj))))
		exit(1);
	bzero(filler->piece, sizeof(t_obj));
	if (!(filler->heat = (t_heat*)ft_memalloc(sizeof(t_heat))))
		exit(1);
	bzero(filler->heat, sizeof(t_heat));
	set_player_info(filler);
	set_map(filler->map);
	set_piece(filler->piece);
	set_heat_map(filler);
}

int		main(void)
{
	t_filler	*filler;
	char		*line;

	if (!(filler = (t_filler*)ft_memalloc(sizeof(t_filler))))
		exit(1);
	set_filler(filler);
	place_piece(filler);
	free_obj(filler->piece);
	while (1)
	{
		get_next_line(0, &line);
		free(line);
		rew_map(filler->map);
		rew_heat_map(filler);
		set_piece(filler->piece);
		if (place_piece(filler) == 1)
		{
			free_all(&filler);
			return (1);
		}
		free_obj(filler->piece);
	}
	return (0);
}
