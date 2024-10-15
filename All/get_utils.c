/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:38:03 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/14 11:19:43 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

char	*get_next_value(char **str)
{
	char	*start;

	while (is_whitespace(**str))
		(*str)++;
	start = *str;
	while (**str && !is_whitespace(**str) && **str != ',')
		(*str)++;
	if (start == *str)
		return (NULL);
	if (**str == ',')
	{
		**str = '\0';
		(*str)++;
	}
	else if (**str)
	{
		**str = '\0';
		(*str)++;
	}
	return (start);
}

void	set_rgb(float *r, float *g, float *b, char **str)
{
	char	*value;

	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing R value in RGB\n");
	*r = ft_atoi(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing G value in RGB\n");
	*g = ft_atoi(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing B value in RGB\n");
	*b = ft_atoi(value);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		perror_exit("Error: RGB values must be between 0 and 255\n");
}

void	set_nxyz(float *nx, float *ny, float *nz, char **str)
{
	char	*value;

	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing x value in normal vector\n");
	*nx = ft_atof(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing y value in normal vector\n");
	*ny = ft_atof(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing z value in normal vector\n");
	*nz = ft_atof(value);
	if (*nx < -1 || *nx > 1 || *ny < -1 || *ny > 1 || *nz < -1 || *nz > 1)
		perror_exit("Error: Normal vector components range (-1, 1)\n");
}

void	set_xyz(float *x, float *y, float *z, char **str)
{
	char	*value;

	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing x coordinate\n");
	*x = ft_atof(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing y coordinate\n");
	*y = ft_atof(value);
	value = get_next_value(str);
	if (!value)
		perror_exit("Error: Missing z coordinate\n");
	*z = ft_atof(value);
}
