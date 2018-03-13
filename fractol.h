/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 01:39:03 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/17 03:06:53 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"
# include <time.h>

# define FLAG env->info.flg
# define INIT env->mlx.init
# define IMAGE env->mlx.image
# define DATA env->mlx.data
# define SIZE env->mlx.size_line
# define BPP env->mlx.bpp
# define ENDIAN env->mlx.endian
# define WIN env->mlx.window
# define HEIGHT env->info.hauteur
# define WIDTH env->info.largeur
# define ITT env->info.itt
# define BASEX env->info.base_x
# define BASEY env->info.base_y
# define C_R env->calc.c_r
# define C_I env->calc.c_i
# define Z_R env->calc.z_r
# define Z_I env->calc.z_i
# define I env->calc.i
# define ZOOM env->info.zoom
# define TMPI env->calc.tmpi
# define TMPR env->calc.tmpr
# define COLOR env->info.color
# define TIME env->info.time
# define T_TIME env->info.time_tmp
# define ESC 53
# define M_DOWN 4
# define M_UP 5
# define M_LEFT 7
# define M_RIGHT 6
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define PLUS 69
# define MINUS 78
# define MOTION 6
# define MASK 0
# define IM 13
# define IP 1
# define TYPE env->info.type
# define PAUSE env->info.pause
# define FRAME env->info.time_tmp

typedef struct		s_mlx
{
	void			*init;
	void			*window;
	void			*image;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_info
{
	int				flg;
	double			largeur;
	double			hauteur;
	int				itt;
	double			base_x;
	double			base_y;
	double			zoom;
	int				color;
	double			time;
	int				pause;
	double			time_tmp;
	char			*type;
	int				j;
	int				menu;
}					t_info;

typedef struct		s_calc
{
	double			z_i;
	double			tmpi;
	double			tmpr;
	double			z_r;
	double			c_i;
	double			c_r;
	int				i;
}					t_calc;

typedef struct		s_choose
{
	void			*img;
	void			*win;
	char			*data;
	int				bpp;
	char			*file;
	int				sizel;
	int				endian;
	int				hauteur;
	int				largeur;
}					t_choose;

typedef struct		s_fract
{
	t_info			info;
	t_mlx			mlx;
	t_calc			calc;
	t_choose		texture;
}					t_fract;

void				chooseurfighter(t_fract *env);
int					gere_expose2(t_fract *env);
void				mandel(int x, int y, t_fract *env);
void				ft_select(int x, int y, t_fract *env);
void				lauch_factory(t_fract *env);
void				init(t_fract **env);
void				pixel_to_image(int x, int y, t_fract *env);
int					k_hook(int keycode, t_fract *env);
int					gere_expose(t_fract *env);
void				give_me_ur_id(t_fract *env);
void				ft_hud(t_fract *env);
void				birdofprey(int x, int y, t_fract *env);
void				burning_turn_down(int x, int y, t_fract *env);
void				juliabird(int x, int y, t_fract *env);

#endif
