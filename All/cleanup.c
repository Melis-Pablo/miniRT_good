/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:47:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/12 13:40:02 by pmelis           ###   ########.fr       */
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
	}
	return (ret);
}
