/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 19:18:13 by rlintill          #+#    #+#             */
/*   Updated: 2020/08/14 19:18:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define W width
# define O opponent
# define M map

# include "libft.h"
# include "get_next_line.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_obj
{
	int			height;
	int			width;
	char		**fig;
}				t_obj;

typedef struct	s_heat
{
	int			height;
	int			width;
	int			**fig;
}				t_heat;

typedef struct	s_filler
{
	char		me;
	char		opponent;
	t_obj		*map;
	t_obj		*piece;
	t_heat		*heat;
}				t_filler;

/*
**	free.c
*/

void			free_heat(t_heat *heat);
void			free_obj(t_obj *obj);
void			free_all(t_filler **filler);

/*
**	piece.c
*/

void			set_piece(t_obj *piece);
int				place_piece(t_filler *filler);

/*
**	utils.c
*/

int				length_num(int a);
int				mod(int a);
void			print_res(t_point coord);

/*
**	heat.c
*/

void			set_heat_map(t_filler *f);
void			rew_heat_map(t_filler *filler);

#endif
