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

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_obj
{
	int			height;
	int			width;
	char**		fig;
}				t_obj;

typedef struct	s_heat
{
	int			height;
	int			width;
	int**		fig;
}				t_heat;

typedef struct	s_filler
{
	char		me;
	char		opponent;
	t_obj		*map;
	t_obj		*piece;
	t_heat		*heat;
}				t_filler;

#endif
