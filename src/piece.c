/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:39:16 by rlintill          #+#    #+#             */
/*   Updated: 2020/09/15 15:35:23 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		set_piece(t_obj *piece)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	piece->height = ft_atoi(&line[5]);
	piece->width = ft_atoi(&line[5 + length_num(piece->height)]);
	free(line);
	i = 0;
	if (!(piece->fig = (char **)malloc(sizeof(char *) * (piece->height + 1))))
		exit(1);
	i = 0;
	while (i < piece->height)
	{
		get_next_line(0, &line);
		piece->fig[i] = ft_strdup(line);
		free(line);
		i++;
	}
	piece->fig[i] = NULL;
}

static int	estimate_grad(t_obj *piece, t_heat *heat, int y, int x)
{
	int		can_set;
	int		i;
	int		j;
	int		res;

	can_set = -1;
	i = -1;
	res = 0;
	while (++i < piece->height)
	{
		j = -1;
		while (++j < piece->width)
		{
			if ((piece->fig[i][j] == '*') && (heat->fig[i + y][j + x] == 0
				|| (heat->fig[i + y][j + x] == -1 && can_set == 1)))
				return (-1);
			if (piece->fig[i][j] == '*' && heat->fig[i + y][j + x] == -1)
				can_set = 1;
			else if (piece->fig[i][j] == '*')
				res += heat->fig[i + y][j + x];
		}
	}
	return (can_set == 1 ? res : -1);
}

static void	set_grad(t_heat *grad, t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	grad->height = filler->heat->height - filler->piece->height + 1;
	grad->width = filler->heat->width - filler->piece->width + 1;
	if (!(grad->fig = (int **)malloc(sizeof(int *) * (grad->height + 1))))
		exit(1);
	while (i < grad->height)
	{
		j = 0;
		if (!(grad->fig[i] = (int *)malloc(sizeof(int) * (grad->width + 1))))
			exit(1);
		while (j < grad->width)
		{
			grad->fig[i][j] = estimate_grad(filler->piece, filler->heat, i, j);
			j++;
		}
		i++;
	}
}

static int	count_coord(t_heat *grad)
{
	t_point	coord;
	int		min;
	int		i;
	int		j;

	i = -1;
	coord.x = 0;
	coord.y = 0;
	min = 2147483647;
	while (++i < grad->height)
	{
		j = -1;
		while (++j < grad->width)
		{
			if (grad->fig[i][j] < min && grad->fig[i][j] >= 0)
			{
				min = grad->fig[i][j];
				coord.x = j;
				coord.y = i;
			}
		}
	}
	print_res(coord);
	i = (min == 2147483647) ? 1 : 0;
	return (i);
}

int			place_piece(t_filler *filler)
{
	t_heat	*grad;

	if (!(grad = (t_heat*)ft_memalloc(sizeof(t_heat))))
		exit(1);
	bzero(grad, sizeof(t_heat));
	set_grad(grad, filler);
	if (count_coord(grad) == 1)
	{
		free_heat(grad);
		free(grad);
		return (1);
	}
	free_heat(grad);
	free(grad);
	return (0);
}
