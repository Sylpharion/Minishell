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
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp && shell->splitline[1])
	{
		ft_putstr(shell->splitline[1]);
		ft_putendl(": No such file of directory.");
		free(tmp);
		return ;
	}
	else if (!tmp && !shell->splitline[1])
	{
		ft_cd_home(shell);
		free(tmp);
		return ;
	}
	else
		free(tmp);
	ft_true_cd(shell);
	free(shell->pathdir);
}

void		ft_true_cd(t_shell *shell)
{
	ft_verif_cd(shell, 0, 0, 0);
	if (ft_tablen(shell->splitline) > 2)
		ft_putendl("cd: Too many arguments.");
	else if (!shell->splitline[1] || ft_strcmp(shell->splitline[1], "--") == 0)
		ft_cd_home(shell);
	else if (ft_strcmp(shell->splitline[1], "-") == 0)
		ft_cd_moins(shell);
	else
		ft_exec_cd(shell);
}

void		ft_cd_moins(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "OLDPWD") == 0)
		{
			free(tmp);
			tmp = ft_cut_val(shell->env_cpy[i]);
			break ;
		}
		free(tmp);
		i++;
	}
	if (chdir(tmp) == -1)
		ft_cd_error(shell->splitline[1]);
	else
		ft_new_oldpwd(shell, 0, NULL);
	free(tmp);
}

void		ft_exec_cd(t_shell *shell)
{
	if (chdir(shell->pathdir) == -1)
		ft_cd_error(shell->splitline[1]);
	else
		ft_new_oldpwd(shell, 0, NULL);
}

void		ft_cd_home(t_shell *shell)
{
	if (chdir(shell->home) == -1)
		ft_cd_home_error(shell, shell->home);
	else
		ft_new_oldpwd(shell, 0, NULL);
	return ;
}
