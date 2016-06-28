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

void		ft_env(t_shell *shell)
{
	//if (ft_tablen(shell->splitline) == 1)
	//ft_printenv(shell);
	int i;

	i = 0;
	while (shell->env_cpy[i])
	{
		ft_putendl(shell->env_cpy[i]);
		i++;
	}
}

void		ft_printenv(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strcmp(shell->splitline[0], "printenv") == 0 && ft_tablen(shell->splitline) > 2)
	{
		ft_putendl("printenv: Too many arguments.");
		return ;
	}
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (!shell->splitline[1])
			ft_putendl(shell->env_cpy[i]);
		else if (ft_strcmp(shell->splitline[1], tmp) == 0)
		{
			ft_print_arg(shell->env_cpy[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

void		ft_print_arg(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	i++;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void		ft_parse_env(t_shell *shell, char *env[])
{
	int		i;
	int		n;
	char *tmp;

	i = 0;
	n = 0;
	 while (env[i])
		i++;
	shell->env_cpy = (char **)malloc(sizeof(char *) * i + 1);
	n = i;
	i = 0;
	while (i < n)
	{
		shell->env_cpy[i] = ft_strnew(ft_strlen(env[i]));
		i++;
	}
	n = i;
	i = 0;
	while (i < n)
	{
		if (strncmp(env[i], "SHLVL", 5) != 0)
			ft_strcpy(shell->env_cpy[i], env[i]);
		else
		{
			ft_strcat(shell->env_cpy[i], "SHLVL=");
			tmp = ft_itoa(ft_atoi(&env[i][6]) + 1);
			ft_strcat(shell->env_cpy[i], tmp);
		}
	 	i++;
	}
	free(tmp);
	shell->env_cpy[i] = NULL;
}

void		ft_create_env(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	shell->pwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", shell->pwd);
	oldpwd = ft_strjoin("OLDPWD=", shell->pwd);
	shell->env_cpy = (char **)malloc(sizeof(char *) * 7);
	shell->env_cpy[0] = ft_strdup("HOME=/nfs/2014/s/smassand");
	shell->env_cpy[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/\
sbin:/usr/local/bin:/usr/local/munki");
	shell->env_cpy[2] = ft_strdup("SHLVL=1");
	shell->env_cpy[3] = ft_strdup(pwd);
	shell->env_cpy[4] = ft_strdup(oldpwd);
	shell->env_cpy[5] = ft_strdup("_=/usr/bin/env");
	shell->env_cpy[6] = NULL;
	free(pwd);
	free(oldpwd);
}
