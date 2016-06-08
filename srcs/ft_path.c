/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:56:55 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:57:00 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_path(t_shell *shell, char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (strncmp(env[i], "PATH", 4) != 0)
		i++;
	s = ft_strnew(ft_strlen(env[i]) + 1);
	ft_strcpy(s, env[i]);
	ft_parse_path(shell, s);
}

void		ft_parse_path(t_shell *shell, char *s)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s[i] != '=')
		i++;
	i++;
	s2 = ft_strnew(ft_strlen(s) - i);
	while (s[i])
	{
		s2[j] = s[i];
		j++;
		i++;
	}
	free(s);
	shell->path = ft_strsplit(s2, ':');
	free(s2);
}