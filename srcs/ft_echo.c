/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 18:48:03 by smassand          #+#    #+#             */
/*   Updated: 2016/06/22 18:48:08 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_echo(t_shell *shell)
{
	int		i;

	i = 1;
	if (ft_tablen(shell->splitline) != 1)
	{
		while (shell->splitline[i])
		{
			if (shell->splitline[i][0] == '$')
				ft_echo_var(shell->env_cpy, shell->splitline[i]);
			else if (shell->splitline[i][0] == '"' && 
				shell->splitline[i][ft_strlen(shell->splitline[i]) - 1] == '"')
				ft_echo_quote(shell->splitline[i]);
			else
				ft_echo_brut(shell->splitline[i]);
			i++;
			ft_putchar(' ');
		}
	}
	ft_putchar('\n');
}

void		ft_echo_var(char **env, char *str)
{
	char	*str2;
	int		i;
	int		j;

	i = 1;
	j = 0;
	str2 = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		str2[j] = str[i];
		i++;
		j++;
	}
	str2[j] = 0;
	ft_print_var(env, str2);
	free(str2);
}

void		ft_print_var(char **env, char *str)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(str, ft_cut_arg(env[i])) == 0)
		{
			ft_print_arg(env[i]);
			return ;
		}
		i++;
	}
}

void		ft_echo_quote(char *str)
{
	(void)str;
}

void		ft_echo_brut(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			ft_putchar(str[i]);
		i++;
	}
}
