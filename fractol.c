/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 04:24:35 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/18 04:35:22 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** On initialise les variables et lance la mlx.
*/

void		init(t_fract **env)
{
	(*env)->info.hauteur = 700;
	(*env)->info.largeur = 700;
	(*env)->mlx.init = mlx_init();
	(*env)->mlx.window = mlx_new_window((*env)->mlx.init, (*env)->info.largeur,
			(*env)->info.hauteur, "Fractol");
	(*env)->mlx.image = mlx_new_image((*env)->mlx.init, (*env)->info.largeur,
			(*env)->info.hauteur);
	(*env)->info.base_x = 0;
	(*env)->info.base_y = 0;
	(*env)->info.zoom = 1;
	(*env)->info.itt = 50;
	(*env)->info.color = 420;
	(*env)->calc.c_r = 0;
	(*env)->info.menu = 0;
}

/*
** On donne a C_R et C_I la position de la sourie comme valeur.
** Si PAUSE n'est pas active evidement.
*/

int			mouse_pos(int x, int y, t_fract *env)
{
	if (PAUSE == 0)
	{
		C_R = ((double)x / (double)WIDTH);
		C_I = ((double)y / (double)HEIGHT);
		lauch_factory(env);
	}
	else
		mlx_string_put(INIT, WIN, 350, 50, 0x960018, "PAUSE");
	return (0);
}

/*
** On utilise le decallage binaire pour assigner notre couleur a notre pixel.
** Ici on multiplie la valeur de la couleur par I pour donner une image psyche.
** la variable pos nous donne les valeurs a modifier sur la string pour changer
** la couleur du pixel actuel.
*/

void		pixel_to_image(int x, int y, t_fract *env)
{
	int		pos;

	pos = (x * BPP / 8) + (y * SIZE);
	DATA[pos] = COLOR * I;
	DATA[pos + 1] = ((COLOR * I) >> 8);
	DATA[pos + 2] = ((COLOR * I) >> 16);
}

/*
** Cette fonction nous permet de zoomer avec la molette de la sourie.
** Si la sourie marche bien haha.
*/

int			mhook(int keycode, int x, int y, t_fract *env)
{
	if (keycode == M_UP)
	{
		ZOOM *= pow(1.001, FRAME);
		BASEX += (x - WIDTH / 2) / (WIDTH / 2 * ZOOM) / 8;
		BASEY += (x - HEIGHT / 2) / (HEIGHT / 2 * ZOOM) / 8;
	}
	else if (keycode == M_DOWN)
	{
		ZOOM /= pow(1.001, FRAME);
		BASEX -= (x - WIDTH / 2) / (WIDTH / 2 * ZOOM) / 8;
		BASEY -= (y - HEIGHT / 2) / (HEIGHT / 2 * ZOOM) / 8;
	}
	else
		return (0);
	lauch_factory(env);
	return (0);
}

/*
** Nous verifions que l'argument soit bien contenu dans ceux desires.
** Ensuite on lance l'affichage de base pour chaques fractales.
** La fonction evenement mouse_pos n'est disponible que sous Julia.
*/

int			main(int argc, char **argv)
{
	t_fract	*env;

	if (!(env = (t_fract *)ft_memalloc(sizeof(t_fract))))
		return (0);
	if (argc == 2)
	{
		if (!(TYPE = ft_memalloc(sizeof(char *) * ft_strlen(argv[1]))))
			return (0);
		ft_strcpy(TYPE, argv[1]);
		init(&env);
		give_me_ur_id(env);
		lauch_factory(env);
		mlx_expose_hook(WIN, gere_expose, env);
		mlx_hook(WIN, 2, 0, k_hook, env);
		mlx_mouse_hook(WIN, mhook, env);
		mlx_hook(WIN, MOTION, 0, mouse_pos, env);
		mlx_loop(INIT);
	}
	else
		ft_putstr("Julia/Mandelbrot/ModBurn/Burning_Ship/BirdOfPrey/JuliaBird");
	return (0);
}
