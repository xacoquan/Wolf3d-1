/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:33:21 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/16 22:00:50 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf3d.h"

static void	load_img(t_mlx *mlx, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx->ptr, path, &img->x, &img->y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp,
								&img->sline, &img->endian);
	img->bpp = img->bpp >> 3;
}

static void	load_gun(t_mlx *mlx)
{
	int		i;
	char	*pathgun[] = {"imgs/gun.xpm", "imgs/gun.xpm", "imgs/gun.xpm",
						"imgs/gun.xpm", "imgs/gun.xpm", "imgs/gun.xpm",
						"imgs/gun.xpm", "imgs/gun.xpm", "imgs/gun.xpm",
						"imgs/gun.xpm", "imgs/gun.xpm"};

	mlx->cur_g = 0;
	i = -1;
	while (++i < 11)
		load_img(mlx, &mlx->gun[i], pathgun[i]);
}

static void	load_wall(t_mlx *mlx)
{
	int		i;
	char	*path[8] = {"imgs/66.xpm", "imgs/33.xpm", "imgs/15.xpm",
						"imgs/72.xpm", "imgs/172.xpm", "imgs/7.xpm",
						"imgs/180.xpm", "imgs/youwin.xpm"};

	i = -1;
	while (++i < 8)
		load_img(mlx, &mlx->wall[i], path[i]);
}

void		init_all(t_mlx *mlx)
{
	int		i;
	t_img	load;

	mlx->x0 = 30.5;
	mlx->y0 = 8.5;
	mlx->a = 4.7;
	i = -1;
	while (++i < 5)
		mlx->event[i] = 0;
	load_img(mlx, &load, "imgs/loading.xpm");
	mlx_put_image_to_window(mlx->ptr, mlx->win, load.ptr,
							(WIN_X - load.x) / 2, (WIN_Y - load.y) / 2);
	mlx->screen.ptr = mlx_new_image(mlx->ptr, WIN_X, WIN_Y);
	mlx->screen.data = mlx_get_data_addr(mlx->screen.ptr, &mlx->screen.bpp,
									&mlx->screen.sline, &mlx->screen.endian);
	mlx->screen.bpp = mlx->screen.bpp >> 3;
	load_img(mlx, &mlx->sky, "imgs/sky.xpm");
	load_wall(mlx);
	load_gun(mlx);
	get_laby(mlx->laby, 1);
	get_laby(mlx->laby_mask, 0);
}
