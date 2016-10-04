/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:25:25 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:25:27 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_maj_pwd(t_shell *shell)
{
	char	**update_env;
	int		i;

	i = 0;
	update_env = (char **)malloc(sizeof(char *)
				* ft_tablen(shell->env_cpy) + 20);
	while (shell->env_cpy[i])
	{
		update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
		update_env[i] = ft_strcat(update_env[i], shell->env_cpy[i]);
		i++;
	}
	update_env[i] = ft_strnew(3 + ft_strlen(shell->pwd) + 2);
	ft_strcat(update_env[i], "PWD");
	ft_strcat(update_env[i], "=");
	ft_strcat(update_env[i], shell->pwd);
	update_env[i + 1] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

void		ft_maj_oldpwd(t_shell *shell)
{
	char	**update_env;
	int		i;

	i = 0;
	update_env = (char **)malloc(sizeof(char *)
				* ft_tablen(shell->env_cpy) + 20);
	while (shell->env_cpy[i])
	{
		update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
		ft_strcat(update_env[i], shell->env_cpy[i]);
		i++;
	}
	update_env[i] = ft_strnew(ft_strlen("OLDPWD") +
						ft_strlen(shell->pwd) + 2);
	ft_strcat(update_env[i], "OLDPWD");
	ft_strcat(update_env[i], "=");
	ft_strcat(update_env[i], shell->pwd);
	update_env[i + 1] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

void		ft_verif_cd(t_shell *shell, int i, int pwd, int oldpwd)
{
	char	*tmp;

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
	if (shell->splitline[1])
		shell->pathdir = ft_verif_cd_pathdir(shell, tmp);
	else
	{
		shell->pathdir = ft_strnew(ft_strlen(shell->home));
		ft_strcpy(shell->pathdir, shell->home);
	}
	ft_strcpy(shell->pathdir, shell->splitline[1]);
}

char		*ft_verif_cd_pathdir(t_shell *shell, char *tmp)
{
	char	*pathdir;

	tmp = getcwd(NULL, 0);
	pathdir = ft_strnew(ft_strlen(tmp) + ft_strlen(shell->splitline[1]));
	ft_strcat(pathdir, tmp);
	ft_strcat(pathdir, shell->splitline[1]);
	free(tmp);
	return (pathdir);
}

void		ft_add_pwd(t_shell *shell, int pwd, int oldpwd)
{
	if (pwd == 0)
		ft_maj_pwd(shell);
	if (oldpwd == 0)
		ft_maj_oldpwd(shell);
}
