/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:25:57 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:26:02 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char		*ft_get_the_line(void)
{
	char	*str;
	int		ret;
	int		buf;

	buf = 1000000;
	str = ft_strnew(buf + 1);
	ret = read(0, str, buf);
	str[ret - 1] = 0;
	return (str);
}

void		ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}
