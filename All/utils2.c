/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:09:02 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/12 12:09:18 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

float	ft_atof(const char	*str)
{
	long	int_part;
	double	dec_part;
	double	power;
	int		sign;

	int_part = 0;
	dec_part = 0.0;
	power = 1.0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -sign;
	while (*str != '.' && *str)
		int_part = (int_part * 10) + (*str++ - 48);
	if (*str == '.')
		str++;
	while (*str)
	{
		power /= 10;
		dec_part = dec_part + (*str++ - 48) * power;
	}
	return ((float)((int_part + dec_part) * sign));
}
