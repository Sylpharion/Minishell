/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:40:52 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:40:55 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_cd_home_error(t_shell *shell, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(tmp, "HOME") == 0)
		{
			free(tmp);
			ft_cd_error(path);
			return ;
		}
		free(tmp);
		i++;
	}
	ft_putendl("cd: No home directory.");
}

void		ft_cd_error(char *path)
{
	struct stat st;

	if (lstat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) == 1)
			ft_putstr("cd: not a directory: ");
		else if (S_ISDIR(st.st_mode) == 1)
			ft_putstr("cd: permission denied: ");
	}
	else
		ft_putstr("cd: no such file of directory: ");
	ft_putendl(path);
}

void		ft_error(t_shell shell)
{
	if (stat(shell.exec, &shell.st) != -1)
	{
		if (access(shell.exec, X_OK) == -1)
			ft_putstr("minishell: permission denied: ");
		else
			ft_putstr("minishell: no such file or directory: ");
	}
	else
		ft_putstr("minishell: command not found: ");
	ft_putendl(shell.splitline[0]);
}
