/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:47 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:49 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_cd(t_shell *shell)
{
	// if (!shell->splitline[1])
	// 	chdir(shell->home);
	ft_verif_cd(shell);
}

void		ft_verif_cd(t_shell *shell)
{
	int		i;
	int		pwd;
	int		oldpwd;
	char	*tmp;

	i = 0;
	pwd = 0;
	oldpwd = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
			pwd = 1;
		else if (ft_strcmp(tmp, "OLDPWD") == 0)
			oldpwd = 1;
		free(tmp);
		i++;
	}
	if (!shell->pwd)
		shell->pwd = getcwd(NULL, 0);
	ft_add_pwd(shell, pwd, oldpwd);
}

void		ft_add_pwd(t_shell *shell, int pwd, int oldpwd)
{
	int		i;
	char	**update_env;
	char	**update_env2;

	i = 0;
	if (pwd == 0)
	{
		update_env = (char **)malloc(sizeof(char *)
					* ft_tablen(shell->env_cpy) + 2);
		while (shell->env_cpy[i])
		{
			update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcat(update_env[i], shell->env_cpy[i]);
			i++;
		}
		update_env[i] = ft_strnew(3 + ft_strlen(shell->pwd) + 2);
		ft_strcat(update_env[i], "PWD");
		ft_strcat(update_env[i], "=");
		ft_strcat(update_env[i], shell->pwd);
		update_env[i + 1] = NULL;
		//ft_free_tab(shell->env_cpy);
		//shell->env_cpy = update_env;
		ft_free_setenv(shell, update_env);
	}

	i = 0;
	if (oldpwd == 0)
	{
		update_env2 = (char **)malloc(sizeof(char *)
					* ft_tablen(shell->env_cpy) + 2);
		while (shell->env_cpy[i])
		{
			update_env2[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcat(update_env2[i], shell->env_cpy[i]);
			i++;
		}
		update_env2[i] = ft_strnew(ft_strlen("OLDPWD") + ft_strlen(shell->pwd) + 2);
		ft_strcat(update_env2[i], "OLDPWD");
		ft_strcat(update_env2[i], "=");
		ft_strcat(update_env2[i], shell->pwd);
		update_env2[i + 1] = NULL;
		//ft_free_tab(shell->env_cpy);
		//shell->env_cpy = update_env2;
		ft_free_setenv(shell, update_env);
	}
}