/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooseurfighter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 22:06:15 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/18 06:18:08 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		change_song(t_fract *env)
{
	system("killall sh | killall afplay");
	if (FLAG == 1)
		system("while :; do afplay .sound/After.mp3 ;done &>/dev/null &");
	if (FLAG == 2)
		system("while :; do afplay .sound/ChanChan.mp3 ;done &>/dev/null &");
	if (FLAG == 3)
		system("while :; do afplay .sound/URSS.mp3 ;done &>/dev/null &");
	if (FLAG == 4)
		system("while :; do afplay .sound/Chicken.mp3 ;done &>/dev/null &");
	if (FLAG == 5)
		system("while :; do afplay .sound/Eurodance.mp3 ;done &>/dev/null &");
	if (FLAG == 6)
		system("while :; do afplay .sound/Sexion.mp3 ;done &>/dev/null &");
}

int			mhook2(int keycode, int x, int y, t_fract *env)
{
	if (keycode == 1 && x > 54 && x < 151 && y > 98 && y < 200)
	{
		system("killall sh | killall afplay");
		system("afplay .sound/fatality.mp3 &>/dev/null &");
		ft_putstr("U ded cz of //DANCEFLOORMASTER// :'$$$$\n");
		exit(42);
	}
	else if (keycode == 1 && x > 166 && x < 259 && y > 99 & y < 196)
		FLAG = 4;
	else if (keycode == 1 && x > 384 && x < 483 && y > 100 && y < 205)
		FLAG = 6;
	else if (keycode == 1 && x > 163 && x < 262 && y > 208 && y < 315)
		FLAG = 3;
	else if (keycode == 1 && x > 271 && x < 372 && y > 211 && y < 313)
		FLAG = 2;
	else if (keycode == 1 && x > 381 && x < 479 && y > 209 && y < 311)
		FLAG = 1;
	else if (keycode == 1 && x > 491 && x < 591 && y > 96 && y < 200)
		FLAG = 5;
	else
		return (0);
	lauch_factory(env);
	change_song(env);
	return (0);
}

int			mousepos2(int x, int y)
{
	static int		sound = 0;

	if (sound != 1 && x > 166 && x < 259 && y > 99 & y < 196)
		!system("afplay .sound/Bird.mp3 &>/dev/null &") && (sound = 1);
	else if (sound != 2 && x > 54 && x < 151 && y > 98 && y < 200)
		!system("afplay .sound/Michael.mp3 &>/dev/null &") && (sound = 2);
	else if (sound != 3 && x > 384 && x < 483 && y > 100 && y < 205)
		!system("afplay .sound/JuliaBird.mp3 &>/dev/null &") && (sound = 3);
	else if (sound != 4 && x > 163 && x < 262 && y > 208 && y < 315)
		!system("afplay .sound/Burning.mp3 &>/dev/null &") && (sound = 4);
	else if (sound != 5 && x > 271 && x < 372 && y > 211 && y < 313)
		!system("afplay .sound/Julia.mp3 &>/dev/null &") && (sound = 5);
	else if (sound != 6 && x > 381 && x < 479 && y > 209 && y < 311)
		!system("afplay .sound/Mandel.mp3 &>/dev/null &") && (sound = 6);
	else if (sound != 7 && x > 491 && x < 591 && y > 96 && y < 200)
		!system("afplay .sound/ModBurn.mp3 &>/dev/null &") && (sound = 7);
	return (0);
}

void		chooseurfighter(t_fract *env)
{
	env->texture.file = "pics/maxresdefault.xpm";
	env->texture.img = mlx_xpm_file_to_image(INIT, env->texture.file,
			&env->texture.largeur, &env->texture.hauteur);
	env->texture.data = mlx_get_data_addr(env->texture.img, &env->texture.bpp,
			&env->texture.sizel, &env->texture.endian);
	env->texture.win = mlx_new_window(INIT, env->texture.largeur,
			env->texture.hauteur, "LETS FIGHT");
	mlx_put_image_to_window(INIT, env->texture.win, env->texture.img, 0, 0);
	mlx_expose_hook(env->texture.win, gere_expose2, env);
	mlx_hook(env->texture.win, MOTION, 0, mousepos2, 0);
	mlx_mouse_hook(env->texture.win, mhook2, env);
}

int			gere_expose2(t_fract *env)
{
	mlx_put_image_to_window(INIT, env->texture.win, env->texture.img, 0, 0);
	return (0);
}
