/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 02:05:51 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/18 04:49:31 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** La fractale de Mandelbrot est defini par Z(n+1) = Z(n^2) + C
** Z = a + ib, ou a et b sont semblable a : x et y.
** Z + Z' = (a + a') + i(b + b')
** En fait on etudie l'itteration de cette suite dans le cas ou Z0 = 0
** Les valeurs de C ou l'ensemble de Mandelbrot ne tend pas vers l'infini sont
** d'un couleur differente
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Pour Julia on donne a C une valeurs constante dans la suite de Mandelbrot
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Pour BurningShip en donne prend la valeur absolue de la partie reelles et
** immaginaire de Zn avant l'elevation au carre.
** La fonction fabs donne la valeurs absolue.
** Sa formule original est z ^ 2 + c
*/

void		ft_burningship(int x, int y, t_fract *env)
{
	if (BASEX == 0)
		BASEX = -0.5;
	C_R = 1.5 * (x - WIDTH / 2) / (0.5 * ZOOM * WIDTH) + BASEX;
	C_I = 1.5 * (y - HEIGHT / 2) / (0.5 * ZOOM * HEIGHT) + BASEY;
	Z_R = 0;
	Z_I = 0;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = (TMPR * TMPR) - (TMPI * TMPI) + C_R;
		Z_I = 2 * fabs(TMPR * TMPI) + C_I;
	}
}

/*
** La valeur de C initial de C est completement arbitraire mais est contenu dans
** la fractale de Mandelbrot. Soit entre -2.1 et 0.6
** sur l'abscisse et -1.2 et 1.2 sur l'ordonnee.
*/

void		ft_julia(int x, int y, t_fract *env)
{
	if (C_R == 0)
	{
		C_R = -0.7 + BASEX;
		C_I = 0.27 + BASEY;
	}
	Z_R = 1.5 * (x - WIDTH / 2) / (0.5 * ZOOM * WIDTH) + BASEX;
	Z_I = (y - HEIGHT / 2) / (0.5 * ZOOM * HEIGHT) + BASEY;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = TMPR * TMPR - TMPI * TMPI + C_R;
		Z_I = 2 * TMPI * TMPR + C_I;
	}
}

/*
** Bon, on va un peu expliquer comment on a pu passer de la suite
** a cet algorithme.
** Nous avons cree deux variable pour C et Z. Partie Reel et partie Immaginaire.
** En premier lieu on set au depart BASEX a -0.5
** pour decaller la fractale vers la droite
** On fait dependre C_R et C_I de x et y par rapport a la taille de
** la fenetre et du ZOOM
** pour avoir une image qui s'affiche bien belle toussa.
** On peut trouver que Z_R = (Z_R ^ 2) - (Z_I ^ 2) + C_R.
** Et Z_I = 2 * Z_R * Z_I + C_I.
** On va voir a chaque fois si a un nombre d'itteration raisonnable
** la suite depasse 2.
** Ici 4 car on regarde leur valeurs absolue soit (Z_R ^ 2) + (Z_I ^ 2) < 4.
** On creer des variable tampon, TMPR et TMPI. Voila Voila.
*/

void		ft_mandel(int x, int y, t_fract *env)
{
	if (BASEX == 0)
		BASEX = -0.5;
	C_R = 1.5 * (x - WIDTH / 2) / (0.5 * ZOOM * WIDTH) + BASEX;
	C_I = (y - HEIGHT / 2) / (0.5 * ZOOM * HEIGHT) + BASEY;
	Z_R = 0;
	Z_I = 0;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = TMPR * TMPR - TMPI * TMPI + C_R;
		Z_I = 2 * TMPI * TMPR + C_I;
	}
}

/*
** La selection de la fractale a afficher.
*/

void		ft_select(int x, int y, t_fract *env)
{
	if (FLAG == 1)
		ft_mandel(x, y, env);
	else if (FLAG == 2)
		ft_julia(x, y, env);
	else if (FLAG == 3)
		ft_burningship(x, y, env);
	else if (FLAG == 4)
		birdofprey(x, y, env);
	else if (FLAG == 5)
		burning_turn_down(x, y, env);
	else if (FLAG == 6)
		juliabird(x, y, env);
	else
	{
		ft_putstr("Julia/Mandelbrot/ModBurn/Burning_Ship/BirdOfPrey/JuliaBird");
		exit(42);
	}
}

/*
** On fait tourner la machine pour tous les points de l'image et on les dessine
** en fonction de l'itteration.
*/

void		lauch_factory(t_fract *env)
{
	int		x;
	int		y;

	DATA = mlx_get_data_addr(IMAGE, &BPP, &SIZE, &ENDIAN);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ft_select(x, y, env);
			pixel_to_image(x, y, env);
		}
	}
	mlx_put_image_to_window(INIT, WIN, IMAGE, 0, 0);
	ft_hud(env);
	T_TIME = TIME / CLOCKS_PER_SEC * 10;
	TIME = clock();
}
