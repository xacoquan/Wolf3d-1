/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:32:52 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/16 17:27:58 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "wolf3d.h"

void				pxl_putimg(t_mlx *mlx, int x, int y, unsigned int color)
{
	int				i;
	int				dest;
	unsigned int	new_color;

	new_color = mlx_get_color_value(mlx->ptr, color);
	dest = y * mlx->screen.sline + x * mlx->screen.bpp;
	i = -1;
	while (++i < mlx->screen.bpp)
	{
		if (mlx->screen.endian == 0)
			mlx->screen.data[dest + i] = new_color >> (i << 3) & 0xFF;
		else
			mlx->screen.data[dest + i] = new_color
				>> (mlx->screen.bpp - ((i + 1) << 3)) & 0xFF;
	}
}

static void			pxl_putimg_texture(t_mlx *mlx, t_img *img,
										t_int pos, t_int wall)
{
	int				i;
	int				src;
	int				dest;
	int				cur;

	src = wall.y * img->sline + wall.x * img->bpp;
	dest = pos.y * mlx->screen.sline + pos.x * mlx->screen.bpp;
	i = -1;
	while (++i < img->bpp)
	{
		if (mlx->k >= 1.0)
		{
			cur = img->data[src + i];
			cur += (cur < 0 ? 0xFF : 0);
			cur *= (1.0 / mlx->k);
			cur = (cur > 0xFF ? 0xFF : cur);
			cur = (cur < 0 ? 0 : cur);
			cur = (cur > 127 ? cur - 256 : cur);
			mlx->screen.data[dest + i] = cur;
		}
		else
			mlx->screen.data[dest + i] = img->data[src + i];
	}
}

static void			pxl_putskybox(t_mlx *mlx, t_int pos)
{
	float			save_k;
	t_int			wall;

	wall.x = (mlx->sky.x / (2.0 * M_PI)) * -mlx->a + pos.x;
	wall.x += (wall.x < 0 ? mlx->sky.x : 0);
	wall.y = (pos.y / (WIN_Y / 2.0)) * mlx->sky.y;
	save_k = mlx->k;
	mlx->k = 0;
	pxl_putimg_texture(mlx, &mlx->sky, pos, wall);
	mlx->k = save_k;
}

static unsigned int	dark_color(unsigned int color, int y)
{
	int				i;
	float			k;
	int				n_color[3];

	k = 1.0 - (WIN_Y - y) / (WIN_Y / 2.0);
	k = k / 3.0;
	i = -1;
	while (++i < 3)
	{
		n_color[i] = (color >> ((2 - i) << 3)) & 0xFF;
		n_color[i] = n_color[i] * k;
		n_color[i] = (n_color[i] > 0xFF ? 0xFF : n_color[i]);
		n_color[i] = (n_color[i] < 0 ? 0 : n_color[i]);
	}
	return ((n_color[0] << 16) + (n_color[1] << 8) + n_color[2]);
}

void				fill_img(t_mlx *mlx, int x, int wall_size, float percx)
{
	t_int			pos;
	t_int			wall;
	float			min_w;
	float			max_w;

	pos.x = x;
	pos.y = -1;
	min_w = WIN_Y / 2.0 - wall_size;
	max_w = WIN_Y / 2.0 + wall_size;
	while (++pos.y < WIN_Y)
	{
		wall.x = percx * mlx->w_cur.x;
		wall.y = ((float)(pos.y - min_w) / (max_w - min_w)) * mlx->w_cur.y;
		if (pos.y < min_w)
			pxl_putskybox(mlx, pos);
		else if (pos.y < max_w)
			pxl_putimg_texture(mlx, &mlx->w_cur, pos, wall);
		else
			pxl_putimg(mlx, pos.x, pos.y, dark_color(0x333333, pos.y));
	}
}
