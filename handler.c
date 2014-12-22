/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:33:05 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/19 19:00:40 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include "wolf3d.h"

static void		moove(t_mlx *mlx, int dir)
{
	float		x;
	float		y;

	x = mlx->x0 + dir * cos(mlx->a) * 0.15;
	y = mlx->y0 + dir * sin(mlx->a) * 0.15;
	if (mlx->laby[(int)x][(int)y] != '0')
	{
		if (mlx->laby[(int)mlx->x0][(int)y] == '0')
			mlx->y0 = y;
		else if (mlx->laby[(int)x][(int)mlx->y0] == '0')
			mlx->x0 = x;
	}
	else
	{
		mlx->x0 = x;
		mlx->y0 = y;
	}
}

int				get_keypress(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_GUN && mlx->cur_g == 0)
		mlx->event[FIRE_GUN] = 1;
	if (keycode == KEY_GUN)
		toggle(mlx);
	if (keycode == KEY_QUIT)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_UP || keycode == 'z' || keycode == 'w')
		mlx->event[MOOVE_UP] = 1;
	if (keycode == KEY_LEFT || keycode == 'q' || keycode == 'a')
		mlx->event[ROTATE_LEFT] = 1;
	if (keycode == KEY_DOWN || keycode == 's')
		mlx->event[MOOVE_DOWN] = 1;
	if (keycode == KEY_RIGHT || keycode == 'd')
		mlx->event[ROTATE_RIGHT] = 1;
	return (0);
}

int				get_keyrelease(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_UP || keycode == 'z' || keycode == 'w')
		mlx->event[MOOVE_UP] = 0;
	if (keycode == KEY_LEFT || keycode == 'q' || keycode == 'a')
		mlx->event[ROTATE_LEFT] = 0;
	if (keycode == KEY_DOWN || keycode == 's')
		mlx->event[MOOVE_DOWN] = 0;
	if (keycode == KEY_RIGHT || keycode == 'd')
		mlx->event[ROTATE_RIGHT] = 0;
	return (0);
}

int				get_loop(t_mlx *mlx)
{
	int			flag;

	flag = 0;
	if (mlx->event[MOOVE_UP] && (flag = 1))
		moove(mlx, 1);
	if (mlx->event[MOOVE_DOWN] && (flag = 1))
		moove(mlx, -1);
	if (mlx->event[ROTATE_LEFT] && (flag = 1))
		mlx->a += (mlx->a + 0.1 > 2 * M_PI ? -2 * M_PI + 0.1 : 0.1);
	if (mlx->event[ROTATE_RIGHT] && (flag = 1))
		mlx->a += (mlx->a - 0.1 < -2 * M_PI ? 2 * M_PI - 0.1 : -0.1);
	if (mlx->event[FIRE_GUN] && (flag = 1))
	{
		mlx->cur_g = (mlx->cur_g < 10 ? mlx->cur_g + 1 : 0);
		mlx->event[FIRE_GUN] = (mlx->cur_g ? 1 : 0);
	}
	if (!flag)
		return (0);
	draw_wolf3d(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.ptr, 0, 0);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->gun[mlx->cur_g].ptr,
							(WIN_X - mlx->gun[mlx->cur_g].x) / 2,
							WIN_Y - mlx->gun[mlx->cur_g].y);
	return (0);
}

int				get_expose(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.ptr, 0, 0);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->gun[mlx->cur_g].ptr,
							(WIN_X - mlx->gun[mlx->cur_g].x) / 2,
							WIN_Y - mlx->gun[mlx->cur_g].y);
	return (0);
}
