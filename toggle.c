/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minecraft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:33:59 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/19 18:56:46 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "wolf3d.h"

void		toggle(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->x0 + cos(mlx->a) * 0.9;
	y = mlx->y0 + sin(mlx->a) * 0.9;
	if ((int)x > 0 && (int)x < MAP_X - 1 && (int)y > 0 && (int)y < MAP_Y - 1
		&& mlx->laby[(int)x][(int)y] == '7')
	{
		mlx->laby[(int)x][(int)y] = '0';
		draw_wolf3d(mlx);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.ptr, 0, 0);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->gun[mlx->cur_g].ptr,
								(WIN_X - mlx->gun[mlx->cur_g].x) / 2,
								WIN_Y - mlx->gun[mlx->cur_g].y);
	}
}
