/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:51:33 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/14 11:27:27 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

t_ambient_light	*get_a(char *line)
{
	char			*value;
	t_ambient_light	*ambient;

	ambient = malloc(sizeof(t_ambient_light));
	if (!ambient)
		perror_exit("Error: Memory allocation failed\n");
	value = get_next_value(&line);
	value = get_next_value(&line);
	if (!value)
		perror_exit_free("Error: Missing ambient light intensity\n", ambient);
	ambient->intensity = ft_atof(value);
	if (ambient->intensity < 0 || ambient->intensity > 1)
		perror_exit_free(
			"Error: Ambient light intensity must be between 0.0 and 1.0\n",
			ambient);
	set_rgb(&ambient->color.x, &ambient->color.y, &ambient->color.z, &line);
	normalize_colors(&ambient->color);
	return (ambient);
}

t_camera	*get_c(char *line)
{
	t_camera	*camera;
	char		*value;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		perror_exit("Error: Memory allocation failed\n");
	value = get_next_value(&line);
	set_xyz(&camera->position.x, &camera->position.y, &camera->position.z,
		&line);
	set_nxyz(&camera->direction.x, &camera->direction.y, &camera->direction.z,
		&line);
	value = get_next_value(&line);
	if (!value)
		perror_exit_free("Error: Missing camera FOV\n", camera);
	camera->fov = ft_atoi(value);
	if (camera->fov < 0 || camera->fov > 180)
		perror_exit_free("Error: FOV must be between 0 and 180\n", camera);
	return (camera);
}

void	get_l(char *line, t_scene *scene)
{
	char	*value;

	value = get_next_value(&line);
	set_xyz(&scene->lights[scene->light_count].position.x,
		&scene->lights[scene->light_count].position.y,
		&scene->lights[scene->light_count].position.z, &line);
	value = get_next_value(&line);
	if (!value)
		perror_exit("Error: Missing light brightness intensity\n");
	scene->lights[scene->light_count].intensity = ft_atof(value);
	if (scene->lights[scene->light_count].intensity < 0
		|| scene->lights[scene->light_count].intensity > 1)
		perror_exit(
			"Error: Light brightness intensity must be between 0.0 and 1.0\n");
	set_rgb(&scene->lights[scene->light_count].color.x,
		&scene->lights[scene->light_count].color.y,
		&scene->lights[scene->light_count].color.z, &line);
	normalize_colors(&scene->lights[scene->light_count].color);
}
