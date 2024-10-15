/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:46 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/15 12:14:58 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "miniHope.h"

#define NUM_THREADS 4

typedef struct s_thread_data
{
	t_data	img;
	t_scene	*scene;
	int		start_row;
	int		end_row;
}	t_thread_data;

void	*thread_fill_window(void *arg)
{
	t_thread_data	*data;
	int				j;
	int				i;
	int				c;
	t_vec3			color;

	data = (t_thread_data *)arg;
	j = data->end_row - 1;
	while (j >= data->start_row)
	{
		i = 0;
		while (i < data->scene->width)
		{
			color = anti_alias_pixel(i, j, data->scene->anti_aliasing_samples,
					data->scene);
			color.x = (int)(255.99 * fminf(color.x, 1.0f));
			color.y = (int)(255.99 * fminf(color.y, 1.0f));
			color.z = (int)(255.99 * fminf(color.z, 1.0f));
			c = create_trgb(color.x, color.y, color.z);
			my_mlx_pixel_put(&data->img, i, j, c);
			++i;
		}
		--j;
	}
	return (NULL);
}

void	fill_window(t_data img, t_scene *scene)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_args[NUM_THREADS];
	int				rows_per_thread;
	int				i;

	i = 0;
	rows_per_thread = scene->height / NUM_THREADS;
	while (i < NUM_THREADS)
	{
		thread_args[i].img = img;
		thread_args[i].scene = scene;
		thread_args[i].start_row = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_args[i].end_row = scene->height;
		else
			thread_args[i].end_row = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, thread_fill_window, &thread_args[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
