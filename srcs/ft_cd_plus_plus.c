/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_plus_plus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:43:50 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:43:52 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_init_pwd(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
		{
			pwd = ft_cut_val(shell->env_cpy[i]);
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	return (pwd);
}

void		ft_new_oldpwd(t_shell *shell, int i, char *tmp)
{
	char	**update_env;
	char	*pwd;

	update_env = (char **)malloc(sizeof(char *) *
					ft_tablen(shell->env_cpy) + 1);
	pwd = ft_init_pwd(shell);
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "PWD") == 0)
			update_env[i] = ft_pwd_loop(shell);
		else if (ft_strcmp(tmp, "OLDPWD") == 0)
			update_env[i] = ft_oldpwd_loop(pwd);
		else
		{
			update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcpy(update_env[i], shell->env_cpy[i]);
		}
		free(tmp);
		i++;
	}
	free(pwd);
	update_env[i] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

char		*ft_pwd_loop(t_shell *shell)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strnew(ft_strlen(shell->pwd) + 5);
	tmp2 = getcwd(NULL, 0);
	ft_strcat(tmp, "PWD=");
	ft_strcat(tmp, tmp2);
	pwd = ft_strnew(ft_strlen(tmp));
	ft_strcpy(pwd, tmp);
	free(tmp2);
	free(tmp);
	return (pwd);
}

char		*ft_oldpwd_loop(char *pwd)
{
	char	*oldpwd;

	oldpwd = ft_strnew(ft_strlen(pwd) + 8);
	ft_strcat(oldpwd, "OLDPWD=");
	ft_strcat(oldpwd, pwd);
	return (oldpwd);
}
