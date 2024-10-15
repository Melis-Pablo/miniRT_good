/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_extras.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:54:29 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/12 14:59:41 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb( int r, int g, int b)
{
	int	t;

	t = 0X00;
	return (t << 24 | r << 16 | g << 8 | b);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == MAIN_PAD_ESC)
	{
		free_scene(scene, 0);
		exit(0);
	}
	return (0);
}
