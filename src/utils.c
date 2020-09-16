/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:39:16 by rlintill          #+#    #+#             */
/*   Updated: 2020/09/15 15:35:23 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		length_num(int a)
{
	int len;

	len = 1;
	while (a > 0)
	{
		a /= 10;
		len++;
	}
	return (len);
}

int		mod(int a)
{
	return (a >= 0 ? a : -1 * a);
}

void	print_res(t_point coord)
{
	ft_putnbr(coord.y);
	ft_putchar(' ');
	ft_putnbr(coord.x);
	ft_putchar('\n');
}
