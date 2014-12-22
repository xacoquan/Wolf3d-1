/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:34:10 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/16 04:45:53 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

static void			minimap_vision(t_mlx *mlx)
{
	t_dbl			vision;
	float			dist;
	float			mod_a;

	dist = 0;
	while (dist < 3)
	{
		mod_a = -0.5;
		while (mod_a < 0.5)
		{
			vision.x = mlx->x0 + cos(mlx->a + mod_a) * dist;
			vision.y = mlx->y0 + sin(mlx->a + mod_a) * dist;
			if (vision.x >= 0 && vision.y >= 0
				&& vision.x < MAP_X && vision.y < MAP_Y)
			{
				mlx->laby_mask[(int)vision.x][(int)vision.y] = 1;
				pxl_putimg(mlx, (vision.y * 100.0) / MAP_Y,
							(vision.x * 150.0) / MAP_X, 0xFF6666);
			}
			mod_a += 0.05;
		}
		dist += 0.05;
	}
}

void				minimap(t_mlx *mlx)
{
	t_int			map;
	t_dbl			in_lab;
	unsigned int	color;

	map.x = -1;
	while (++map.x < 150)
	{
		map.y = -1;
		while (++map.y < 150)
		{
			in_lab.x = (map.x * MAP_X) / 150.0;
			in_lab.y = ((150 - map.y) * MAP_Y) / 150.0;
			color = (mlx->laby[(int)in_lab.x][(int)in_lab.y] != '0'
					? 0 : 0xFFFFFF);
			color = (mlx->laby_mask[(int)in_lab.x][(int)in_lab.y]
					? color : 0);
			if (in_lab.x >= mlx->x0 - 0.1 && in_lab.x <= mlx->x0 + 0.1
				&& in_lab.y >= mlx->y0 - 0.1 && in_lab.y <= mlx->y0 + 0.1)
				color = 0xFF0000;
			pxl_putimg(mlx, 150 - map.y, map.x, color);
		}
	}
	minimap_vision(mlx);
}
