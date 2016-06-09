/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:00 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:03 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_env(t_shell shell)
{
	int		i;

	i = 0;
	while(shell.env_cpy[i])
	{
		ft_putendl(shell.env_cpy[i]);
		i++;
	}
}

void		ft_parse_env(t_shell *shell, char *env[])
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	 while (env[i])
		i++;
	shell->env_cpy = (char **)malloc(sizeof(char *) * i + 1);
	n = i;
	i = 0;
	while (i < n)
	{
		if (strncmp(env[i], "SHLVL", 5) != 0)
			shell->env_cpy[i] = ft_strdup(env[i]);
		else
		{
			shell->env_cpy[i] = ft_strnew(ft_strlen(env[i]));
			ft_strcat(shell->env_cpy[i], "SHLVL=");
			ft_strcat(shell->env_cpy[i], ft_itoa(ft_atoi(&env[i][6]) + 1));
		}
	 	i++;
	}
	shell->env_cpy[i] = NULL;
}

void		ft_create_env(t_shell *shell)
{
	char	*str;

	str = ft_strnew(100);
	getcwd(str, 100);
	shell->pwd = ft_strdup(ft_strjoin(str, "/"));
	ft_putendl(shell->pwd);
	shell->env_cpy = (char **)malloc(sizeof(char *) * 7);
	shell->env_cpy[0] = ft_strdup("HOME=/nfs/2014/s/smassand");
	shell->env_cpy[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	shell->env_cpy[2] = ft_strdup("SHLVL=1");
	shell->env_cpy[3] = ft_strdup(ft_strjoin("PWD=", str));
	shell->env_cpy[4] = ft_strdup(ft_strjoin("OLDPWD=", str));
	shell->env_cpy[5] = ft_strdup("_=/usr/bin/env");
	shell->env_cpy[6] = NULL;
}
