/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:47:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/15 22:57:43 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	perror_ret(char *msg)
{
	perror(msg);
	return (1);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	perror_exit_free(char *msg, void *ptr)
{
	perror(msg);
	free(ptr);
	exit(1);
}

int	free_scene(t_scene *scene, int ret)
{
	if (scene)
	{
		if (scene->camera)
			free(scene->camera);
		if (scene->ambient)
			free(scene->ambient);
		free(scene->filename);
		free(scene);
	}
	return (ret);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == MAIN_PAD_ESC)
	{
		free_scene(scene, 0);
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		exit(0);
	}
	return (0);
}
