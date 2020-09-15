/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:39:16 by rlintill          #+#    #+#             */
/*   Updated: 2020/09/15 15:35:23 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_heat(t_heat *heat)
{
	int i;

	i = 0;
	while (i < heat->height)
	{
		ft_memdel((void**)&(heat->fig[i]));
		i++;
	}
	ft_memdel((void**)&(heat->fig));
}

void	free_obj(t_obj *obj)
{
	int i;

	i = 0;
	while (i < obj->height)
	{
		ft_memdel((void**)&(obj->fig[i]));
		i++;
	}
	ft_memdel((void**)&(obj->fig));
}

void	free_all(t_filler **filler)
{
	free_obj((*filler)->map);
	free_heat((*filler)->heat);
	free_obj((*filler)->piece);
	ft_memdel((void**)&((*filler)->map));
	ft_memdel((void**)&((*filler)->heat));
	ft_memdel((void**)&((*filler)->piece));
	ft_memdel((void**)filler);
}
