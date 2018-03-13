/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   birdy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 00:17:24 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/18 05:01:51 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		birdofprey(int x, int y, t_fract *env)
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
		Z_R = (TMPR * TMPR) - (TMPI * TMPI * 3) * fabs(Z_R) + C_R;
		Z_I = ((TMPR * TMPR * 3) - TMPI * TMPI) * fabs(Z_I) + C_I;
	}
}

/*
** Pour le BirdOfPrey,
** Presque comme le burning ship, sauf que l'on eleve la
** puissance de z a 3 soit z^3 + c
** ------------------------------------------------------
** Pour le BurningTurnDown ont soustrait C_R et C_I
** pour avoir un burningship completement retourne.
*/

void		burning_turn_down(int x, int y, t_fract *env)
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
		Z_R = (TMPR * TMPR) - (TMPI * TMPI) - C_R;
		Z_I = 2 * fabs(TMPR * TMPI) - C_I;
	}
}

/*
** Un melange entre julia... et birdofprey...
*/

void		juliabird(int x, int y, t_fract *env)
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
		Z_R = (TMPR * TMPR) - (3 * TMPI * TMPI) * fabs(Z_R) + C_R;
		Z_I = ((TMPR * TMPR * 3) - TMPI * TMPI) * fabs(Z_I) + C_I;
	}
}
