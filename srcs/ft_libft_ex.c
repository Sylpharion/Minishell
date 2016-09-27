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

	str = ft_strnew(BOEUF_SIZE + 1);
	str[BOEUF_SIZE] = 0;
	ret = read(0, str, BOEUF_SIZE);
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
