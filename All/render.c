/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:25:01 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/14 13:39:54 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	intersect_sphere_2(float a, float b, float discriminant, float *t)
{
	float	t0;
	float	t1;

	t0 = (-b - sqrt(discriminant)) / (2.0f * a);
	t1 = (-b + sqrt(discriminant)) / (2.0f * a);
	if (t0 < t1)
		*t = t0;
	else
		*t = t1;
	return (*t > 0);
}

int	intersect_sphere(t_ray ray, t_vec3 center, float radius, float *t)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_subtract(ray.origin, center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	return (intersect_sphere_2(a, b, discriminant, t));
}

int	intersect_plane(t_ray ray, t_vec3 point, t_vec3 normal, float *t)
{
	float	denom;
	t_vec3	p0l0;

	denom = vec3_dot(ray.direction, normal);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = vec3_subtract(point, ray.origin);
		*t = vec3_dot(p0l0, normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

t_vec3	get_cylinder_normal(t_vec3 hit_point, t_object cylinder)
{
	const float	epsilon = 1e-4;
	t_vec3		co;
	float		proj;
	t_vec3		axis_point;

	co = vec3_subtract(hit_point, cylinder.s_cylinder.center);
	proj = vec3_dot(co, cylinder.s_cylinder.axis);
	if (proj <= epsilon)
	{
		return (vec3_multiply(cylinder.s_cylinder.axis, -1));
	}
	else if (proj >= cylinder.s_cylinder.height - epsilon)
	{
		return (cylinder.s_cylinder.axis);
	}
	else
	{
		axis_point = vec3_add(cylinder.s_cylinder.center,
				vec3_multiply(cylinder.s_cylinder.axis, proj));
		return (vec3_normalize(vec3_subtract(hit_point, axis_point)));
	}
}

void	render(t_scene *scene)
{
	void	*mlx;
	void	*win;
	t_data	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, scene->width, scene->height, "MINIRT.01");
	img.img = mlx_new_image(mlx, scene->width, scene->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	print_scene(scene);
	fill_window(img, scene);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_key_hook(win, key_hook, &img);
	mlx_loop(mlx);
}
