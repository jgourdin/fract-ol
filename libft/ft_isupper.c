/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:42:32 by jgourdin          #+#    #+#             */
/*   Updated: 2016/12/01 14:43:26 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else
		return (0);
}
