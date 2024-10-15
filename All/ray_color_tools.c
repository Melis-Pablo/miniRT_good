/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normed4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:05 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/15 11:01:11 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

t_ray	get_ray(float u, float v, t_camera camera)
{
	t_ray_calc	calc;

	calc.theta = camera.fov * M_PI / 180.0;
	calc.half_height = tan(calc.theta / 2);
	calc.half_width = camera.aspect_ratio * calc.half_height;
	calc.w = vec3_multiply(camera.direction, -1);
	calc.u_axis = vec3_normalize(vec3_cross(camera.up, calc.w));
	calc.v_axis = vec3_cross(calc.w, calc.u_axis);
	calc.lower_left_corner = vec3_subtract(camera.position,
			vec3_add(vec3_multiply(calc.u_axis, calc.half_width),
				vec3_add(vec3_multiply(calc.v_axis, calc.half_height),
					calc.w)));
	calc.horizontal = vec3_multiply(calc.u_axis, 2 * calc.half_width);
	calc.vertical = vec3_multiply(calc.v_axis, 2 * calc.half_height);
	calc.direction = vec3_normalize(vec3_subtract(
				vec3_add(calc.lower_left_corner,
					vec3_add(vec3_multiply(calc.horizontal, u),
						vec3_multiply(calc.vertical, v))),
				camera.position));
	return ((t_ray){camera.position, calc.direction});
}

void	set_closest(t_ray_color_calc *calc, int i)
{
	calc->closest_t = calc->t;
	calc->closest_object = i;
}
