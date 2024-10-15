/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:45:51 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/14 11:45:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	get_pl(char *line, t_scene *scene)
{
	char	*value;

	scene->objects[scene->object_count].type = PLANE;
	value = get_next_value(&line);
	set_xyz(&scene->objects[scene->object_count].s_plane.point.x,
		&scene->objects[scene->object_count].s_plane.point.y,
		&scene->objects[scene->object_count].s_plane.point.z, &line);
	set_nxyz(&scene->objects[scene->object_count].s_plane.normal.x,
		&scene->objects[scene->object_count].s_plane.normal.y,
		&scene->objects[scene->object_count].s_plane.normal.z, &line);
	set_rgb(&scene->objects[scene->object_count].color.x,
		&scene->objects[scene->object_count].color.y,
		&scene->objects[scene->object_count].color.z, &line);
	normalize_colors(&scene->objects[scene->object_count].color);
	scene->object_count++;
}

void	get_sp(char *line, t_scene *scene)
{
	char		*value;

	scene->objects[scene->object_count].type = SPHERE;
	value = get_next_value(&line);
	set_xyz(&scene->objects[scene->object_count].s_sphere.center.x,
		&scene->objects[scene->object_count].s_sphere.center.y,
		&scene->objects[scene->object_count].s_sphere.center.z, &line);
	value = get_next_value(&line);
	if (!value)
		perror_exit("Error: Missing sphere diameter\n");
	scene->objects[scene->object_count].s_sphere.radius = ft_atof(value) / 2;
	if (scene->objects[scene->object_count].s_sphere.radius <= 0)
		perror_exit("Error: Sphere diameter must be positive\n");
	set_rgb(&scene->objects[scene->object_count].color.x,
		&scene->objects[scene->object_count].color.y,
		&scene->objects[scene->object_count].color.z, &line);
	normalize_colors(&scene->objects[scene->object_count].color);
	scene->object_count++;
}

void	set_cylinder_attributes(t_object *obj, char **line)
{
	char	*value;

	value = get_next_value(line);
	if (!value)
		perror_exit("Error: Missing cylinder diameter\n");
	obj->s_cylinder.radius = ft_atof(value) / 2;
	value = get_next_value(line);
	if (!value)
		perror_exit("Error: Missing cylinder height\n");
	obj->s_cylinder.height = ft_atof(value);
	if (obj->s_cylinder.radius <= 0 || obj->s_cylinder.height <= 0)
		perror_exit("Error: Cylinder radius and height must be positive\n");
}

void	get_cy(char *line, t_scene *scene)
{
	char		*value;

	scene->objects[scene->object_count].type = CYLINDER;
	value = get_next_value(&line);
	set_xyz(&scene->objects[scene->object_count].s_cylinder.center.x,
		&scene->objects[scene->object_count].s_cylinder.center.y,
		&scene->objects[scene->object_count].s_cylinder.center.z, &line);
	set_nxyz(&scene->objects[scene->object_count].s_cylinder.axis.x,
		&scene->objects[scene->object_count].s_cylinder.axis.y,
		&scene->objects[scene->object_count].s_cylinder.axis.z, &line);
	scene->objects[scene->object_count].s_cylinder.axis
		= vec3_normalize(scene->objects[scene->object_count].s_cylinder.axis);
	set_cylinder_attributes(&scene->objects[scene->object_count], &line);
	set_rgb(&scene->objects[scene->object_count].color.x,
		&scene->objects[scene->object_count].color.y,
		&scene->objects[scene->object_count].color.z, &line);
	normalize_colors(&scene->objects[scene->object_count].color);
	scene->objects[scene->object_count].s_cylinder.base_center
		= vec3_subtract(scene->objects[scene->object_count].s_cylinder.center,
			vec3_multiply(scene->objects[scene->object_count].s_cylinder.axis,
				scene->objects[scene->object_count].s_cylinder.height / 2));
	scene->object_count++;
}
