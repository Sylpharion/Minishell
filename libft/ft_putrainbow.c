/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrainbow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 19:22:23 by smassand          #+#    #+#             */
/*   Updated: 2016/05/12 19:23:01 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char		*ft_rainbow(char *s, char *color)
// {
// 	int		i;
// 	char	*rainbow;

// 	i = 0;
// 	rainbow = ft_strnew(ft_strlen(s) * 2);
// 	while (i < ft_strlen(s))
// 	{
// 		rainbow[i] =
// 		i++;
// 	}
// 	return (s);
// }

void		ft_putrainbow(char *s, char *color)
{
	char	*s2;

	s2 = ft_strnew(ft_strlen(s) + 20);
	// if (ft_strcmp(color, "RAINBOW") == 0)
	// 	s2 = ft_rainbow(s, color);
	// else
	// {
	if (ft_strcmp(color, CANCEL) != 0 && ft_strcmp(color, RED) != 0 &&
		ft_strcmp(color, BLUE) != 0 && ft_strcmp(color, BLACK) != 0 &&
		ft_strcmp(color, GREEN) != 0 && ft_strcmp(color, YELLOW) != 0 &&
		ft_strcmp(color, PURPLE) != 0 && ft_strcmp(color, GREY) != 0 &&
		ft_strcmp(color, CYAN) != 0)
		ft_strcat(s2, CANCEL);
	else
		ft_strcat(s2, color);
	//}
	ft_strcat(s2, s);
	//ft_strcat(s2, "\0");
	ft_putstr(s2);
	ft_putstr(CANCEL);
	free(s2);
}