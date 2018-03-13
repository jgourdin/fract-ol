/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 01:53:40 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/18 06:18:49 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Si on appuie sur C on change totalement la gamme de couleurs.
*/

void		k_hook2(int keycode, t_fract *env)
{
	if (keycode == ESC)
	{
		system("killall sh | killall afplay");
		exit(42);
	}
	else if (keycode == 8)
		COLOR = COLOR + 1100000;
	else if (keycode == 37)
	{
		system("killall sh | killall afplay");
		FLAG = (FLAG == 6 ? 1 : FLAG + 1);
	}
	else if (keycode == 35)
	{
		if (env->info.menu == 0)
			chooseurfighter(env);
		else
			mlx_destroy_window(INIT, env->texture.win);
		env->info.menu = (env->info.menu == 0 ? 1 : 0);
	}
}

void		ft_hud(t_fract *env)
{
	int colortmp;

	colortmp = COLOR + 100000;
	mlx_string_put(INIT, WIN, 30, 30,
		colortmp, "______________________________");
	mlx_string_put(INIT, WIN, 30, 15, colortmp,
			ft_strjoin("I = ", ft_itoa(ITT)));
	mlx_string_put(INIT, WIN, 30, 45,
		colortmp, "|   W = I-- || S = I++       |");
	mlx_string_put(INIT, WIN, 30, 60,
		colortmp, "| R = Reset || SPACE = Pause |");
	mlx_string_put(INIT, WIN, 30, 75,
		colortmp, "|       + - == ZOOM          |");
	mlx_string_put(INIT, WIN, 30, 90,
		colortmp, "|    FLECHE == MOVE          |");
	mlx_string_put(INIT, WIN, 30, 105,
		colortmp, "|    HOLD C == DJ STEVE      |");
	mlx_string_put(INIT, WIN, 30, 120,
		colortmp, "|         L == CHANGE        |");
	mlx_string_put(INIT, WIN, 30, 135,
		colortmp, "|         P == MENU          |");
	mlx_string_put(INIT, WIN, 30, 140,
		colortmp, "______________________________");
}

/*
** On peut ici bouger sur la fractale avec les fleches directionelles,
** on modifie simplement BASEX avec des valeurs contenu dans l'ensemble
** de Mandelbrot mais ce sont des valeurs arbitraires.
** La fonction pow met le premier argument a la puissance du deuxieme.
** On peut augmenter ou reduire l'Itteration max.
** Nous avons ajoute 1 a l'augmentation pour eviter que ca ne bloque a zero.
** Nous avons une fonction Reset.
*/

int			gere_expose(t_fract *env)
{
	mlx_put_image_to_window(INIT, WIN, IMAGE, 0, 0);
	return (0);
}

void		give_me_ur_id(t_fract *env)
{
	if (ft_strcmp(TYPE, "Mandelbrot") == 0)
		FLAG = 1;
	else if (ft_strcmp(TYPE, "Julia") == 0)
		FLAG = 2;
	else if (ft_strcmp(TYPE, "Burning_Ship") == 0)
		FLAG = 3;
	else if (ft_strcmp(TYPE, "BirdOfPrey") == 0)
		FLAG = 4;
	else if (ft_strcmp(TYPE, "ModBurn") == 0)
		FLAG = 5;
	else if (ft_strcmp(TYPE, "JuliaBird") == 0)
		FLAG = 6;
	else
	{
		ft_putstr("Julia/Mandelbrot/ModBurn/Burning_Ship/BirdOfPrey/JuliaBird");
		exit(42);
	}
}

int			k_hook(int keycode, t_fract *env)
{
	if (keycode == 8 || keycode == 37 || keycode == ESC || keycode == 35)
		k_hook2(keycode, env);
	else if (keycode == LEFT || keycode == RIGHT)
		keycode == LEFT ? BASEX -= 0.006 : (BASEX += 0.006);
	else if (keycode == UP || keycode == DOWN)
		keycode == UP ? BASEY -= 0.006 : (BASEY += 0.006);
	else if (keycode == PLUS || keycode == MINUS)
		keycode == PLUS ? (ZOOM *= pow(1.001, FRAME)) :
			(ZOOM /= pow(1.001, FRAME));
	else if (keycode == IM || keycode == IP)
		keycode == IP ? (ITT = ITT * 2 + 1) : (ITT /= 2);
	else if (keycode == 49)
		PAUSE = (PAUSE == 0 ? 1 : 0);
	else if (keycode == 15)
	{
		BASEX = 0;
		BASEY = 0;
		ZOOM = 1;
	}
	else
		return (0);
	lauch_factory(env);
	return (0);
}
