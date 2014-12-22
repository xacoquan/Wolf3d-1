/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:32:40 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/16 04:41:34 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

static float	get_kx(t_mlx *mlx, t_dbl vector)
{
	int			x;
	int			y;
	int			fix;
	float		k;
	float		kx;

	k = 9000;
	x = -1;
	while (++x < MAP_X)
	{
		fix = (vector.x < 0 ? -1 : 0);
		kx = (x - mlx->x0) / vector.x;
		y = mlx->y0 + kx * vector.y;
		if (kx >= 0 && y >= 0 && y < MAP_Y
			&& mlx->laby[x + fix][y] != '0' && kx < k)
			k = kx;
	}
	return (k);
}

static float	get_ky(t_mlx *mlx, t_dbl vector)
{
	int			x;
	int			y;
	int			fix;
	float		k;
	float		ky;

	k = 9000;
	y = -1;
	while (++y < MAP_Y)
	{
		fix = (vector.y < 0 ? -1 : 0);
		ky = (y - mlx->y0) / vector.y;
		x = mlx->x0 + ky * vector.x;
		if (ky >= 0 && x >= 0 && x < MAP_X
			&& mlx->laby[x][y + fix] != '0' && ky < k)
			k = ky;
	}
	return (k);
}

static void		side_and_texture(t_mlx *mlx, int x, t_dbl vector)
{
	int			is_x_side;
	t_dbl		perc;
	t_dbl		k;
	t_int		fix;

	mlx->k = get_kx(mlx, vector);
	if (mlx->k > (k.y = get_ky(mlx, vector)))
	{
		mlx->k = k.y;
		is_x_side = 0;
	}
	else
		is_x_side = 1;
	fix.x = (is_x_side == 1 && vector.x < 0 ? -1 : 0);
	fix.y = (is_x_side == 0 && vector.y < 0 ? -1 : 0);
	perc.x = mlx->x0 + mlx->k * vector.x - (int)(mlx->x0 + mlx->k * vector.x);
	perc.y = mlx->y0 + mlx->k * vector.y - (int)(mlx->y0 + mlx->k * vector.y);
	mlx->w_cur = mlx->wall[
		mlx->laby[(int)(mlx->x0 + mlx->k * vector.x + fix.x)]
		[(int)(mlx->y0 + mlx->k * vector.y + fix.y)] - '1'];
	if (is_x_side)
		fill_img(mlx, x, WIN_Y / (2 * mlx->k), perc.y);
	else
		fill_img(mlx, x, WIN_Y / (2 * mlx->k), perc.x);
}

void			draw_wolf3d(t_mlx *mlx)
{
	int			x;
	float		x1;
	float		y1;
	t_dbl		vector;

	x = -1;
	while (++x < WIN_X)
	{
		y1 = P * (WIN_X / 2 - x) / WIN_X;
		x1 = D * cos(mlx->a) - y1 * sin(mlx->a) + mlx->x0;
		y1 = D * sin(mlx->a) + y1 * cos(mlx->a) + mlx->y0;
		vector.x = x1 - mlx->x0;
		vector.y = y1 - mlx->y0;
		side_and_texture(mlx, x, vector);
	}
	minimap(mlx);
}
