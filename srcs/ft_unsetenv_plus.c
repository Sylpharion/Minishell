/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:25:08 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:25:10 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_cut_arg(char *arg)
{
	int		i;
	char	*res;

	i = 0;
	while (arg[i] != '=')
		i++;
	res = ft_strnew(i + 1);
	i = 0;
	while (arg[i] != '=')
	{
		res[i] = arg[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char		*ft_cut_val(char *arg)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(arg);
	j = 0;
	while (arg[i] != '=')
	{
		i--;
		j++;
	}
	i++;
	res = ft_strnew(j + 1);
	j = 0;
	while (arg[i])
	{
		res[j] = arg[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}
