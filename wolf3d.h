/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsisic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:34:51 by bsisic            #+#    #+#             */
/*   Updated: 2014/12/19 18:59:49 by bsisic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef				WOLF3D_H
# define			WOLF3D_H
# define WIN_X		1024
# define WIN_Y		768
# define P			1.0
# define D			0.5
# define MAP_X		60
# define MAP_Y		64
typedef enum		e_event
{
    MOOVE_UP=		0,
    MOOVE_DOWN=		1,
	ROTATE_LEFT=	2,
	ROTATE_RIGHT=	3,
	FIRE_GUN=		4
}					t_event;
typedef enum		e_key
{
	KEY_UP=			65362,
	KEY_DOWN=		65364,
	KEY_LEFT=		65361,
	KEY_RIGHT=		65363,
	KEY_QUIT=		65307,
	KEY_GUN=		32,
	KEY_MINECRAFT=	65288,
}					t_key;
typedef struct		s_dbl
{
	float			x;
	float			y;
}					t_dbl;
typedef struct		s_int
{
	int				x;
	int				y;
}					t_int;
typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				x;
	int				y;
	int				bpp;
	int				sline;
	int				endian;
}					t_img;
typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	char			laby[MAP_X][MAP_Y];
	char			laby_mask[MAP_X][MAP_Y];
	t_img			screen;
	t_img			sky;
	t_img			wall[8];
	t_img			w_cur;
	t_img			gun[11];
	int				cur_g;
	t_event			event[5];
	float			a;
	float			x0;
	float			y0;
	float			k;
}					t_mlx;
void				init_all(t_mlx *mlx);
void				get_laby(char mlxlaby[MAP_X][MAP_Y], int aff);
void				draw_wolf3d(t_mlx *mlx);
void				check_monsters(t_mlx *mlx);
void				minimap(t_mlx *mlx);
void				pxl_putimg(t_mlx *mlx, int x, int y, unsigned int color);
void				fill_img(t_mlx *mlx, int x, int wall_size, float percx);
int					puterror(char *str);
void				toggle(t_mlx *mlx);
int					get_keypress(int keycode, t_mlx *mlx);
int					get_keyrelease(int keycode, t_mlx *mlx);
int					get_loop(t_mlx *mlx);
int					get_expose(t_mlx *mlx);
#endif				/* !WOLF3D_H */
