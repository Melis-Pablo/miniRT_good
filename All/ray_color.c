/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:02:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/15 11:09:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

t_vec3	ray_color_ret(t_ray ray)
{
	t_vec3	unit_direction;
	float	t_background;
	t_vec3	white;
	t_vec3	blue;

	unit_direction = vec3_normalize(ray.direction);
	t_background = 0.5f * (unit_direction.y + 1.0f);
	white = vec3_create(1.0f, 1.0f, 1.0f);
	blue = vec3_create(0.5f, 0.7f, 1.0f);
	return (vec3_add(vec3_multiply(white, 1.0f - t_background),
			vec3_multiply(blue, t_background)));
}

void	ray_color_loop2(t_scene *scene, t_ray_color_calc *calc)
{
	int	j;

	j = 0;
	while (j < scene->light_count)
	{
		calc->light_dir = vec3_subtract(scene->lights[j].position,
				calc->hit_point);
		calc->light_distance = vec3_length(calc->light_dir);
		calc->light_dir = vec3_normalize(calc->light_dir);
		if (!is_in_shadow(vec3_add(calc->hit_point,
					vec3_multiply(calc->normal, 0.001)),
				calc->light_dir, calc->light_distance, scene))
		{
			calc->diffuse = fmaxf(vec3_dot(calc->normal,
						calc->light_dir), 0.0f);
			calc->diffuse_color = vec3_multiply_components(
					scene->objects[calc->closest_object].color,
					scene->lights[j].color);
			calc->color = vec3_add(calc->color,
					vec3_multiply(calc->diffuse_color,
						calc->diffuse * scene->lights[j].intensity));
		}
		j++;
	}
}

t_vec3	closest_calc(t_scene *scene, t_ray_color_calc *calc, t_ray *ray)
{
	calc->hit_point = vec3_add(ray->origin,
			vec3_multiply(ray->direction, calc->closest_t));
	if (scene->objects[calc->closest_object].type == SPHERE)
	{
		calc->normal = vec3_normalize(vec3_subtract(calc->hit_point,
					scene->objects[calc->closest_object].s_sphere.center));
	}
	else if (scene->objects[calc->closest_object].type == PLANE)
		calc->normal = scene->objects[calc->closest_object].s_plane.normal;
	else if (scene->objects[calc->closest_object].type == CYLINDER)
		calc->normal = get_cylinder_normal(calc->hit_point,
				scene->objects[calc->closest_object]);
	calc->color = vec3_create(0.0f, 0.0f, 0.0f);
	ray_color_loop2(scene, calc);
	calc->max_component = fmaxf(calc->color.x,
			fmaxf(calc->color.y, calc->color.z));
	if (calc->max_component > 1.0f)
		calc->color = vec3_multiply(calc->color, 1.0f
				/ calc->max_component);
	return (calc->color);
}

void	ray_color_loop(t_scene *scene, t_ray *ray, t_ray_color_calc *calc)
{
	calc->i = 0;
	while (calc->i < scene->object_count)
	{
		if (scene->objects[calc->i].type == SPHERE)
		{
			if (intersect_sphere(*ray, scene->objects[calc->i].s_sphere.center,
					scene->objects[calc->i].s_sphere.radius, &calc->t)
				&& calc->t < calc->closest_t)
				set_closest(calc, calc->i);
		}
		else if (scene->objects[calc->i].type == PLANE)
		{
			if (intersect_plane(*ray, scene->objects[calc->i].s_plane.point,
					scene->objects[calc->i].s_plane.normal, &calc->t)
				&& calc->t < calc->closest_t)
				set_closest(calc, calc->i);
		}
		else if (scene->objects[calc->i].type == CYLINDER)
		{
			if (intersect_cylinder(*ray, &scene->objects[calc->i], &calc->t)
				&& calc->t < calc->closest_t)
				set_closest(calc, calc->i);
		}
		calc->i++;
	}
}

t_vec3	ray_color(t_ray ray, t_scene *scene)
{
	t_ray_color_calc	calc;

	calc.closest_t = INFINITY;
	calc.closest_object = -1;
	ray_color_loop(scene, &ray, &calc);
	if (calc.closest_object != -1)
		return (closest_calc(scene, &calc, &ray));
	return (ray_color_ret(ray));
}
