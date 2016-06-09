/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:57:06 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:57:08 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_exec(t_shell shell, char *cmd, char *env[])
{
	char	*str;

	str = NULL;
	if (ft_builtins(shell) == 1)
		return ;
	if (!fork())
	{
		if (execve(shell.exec, shell.splitline, shell.env_cpy) == -1)
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(shell.splitline[0]);
			exit(0);
		}
		free(shell.exec);
	}
	else
		wait(NULL);
}

int			ft_builtins(t_shell shell)
{
	t_ptr	*ptr;
	char	**tab;
	int		i;

	i = 0;
	ptr = ft_ptr_init();
	tab = ft_tab_init();
	while (ft_strcmp(shell.splitline[0], tab[i]) != 0)
		i++;
	if (ptr[i])
	{
		(*ptr[i])(shell);
		return (1);
	}
	else
		return (0);
}

int			ft_isexec(t_shell *shell, char *s)
{
	// if (ft_strncmp(shell->splitline[0], "./", 2) == 0)
	// {
	// 	if (access(ft_strjoin(shell->pwd, ft_strsub(shell->splitline[0], 2, ft_strlen(shell->splitline[0]) - 2)), F_OK | X_OK) != 0)
	// 	{
	// 		shell->exec = shell->splitline[0];
	// 		return (0);
	// 	}
	// 	return (1);
	// }
	// else
	// {
	if (ft_strcmp(shell->splitline[0], "cd") != 0 &&
		ft_strcmp(shell->splitline[0], "env") != 0 &&
		ft_strcmp(shell->splitline[0], "setenv") != 0 &&
		ft_strcmp(shell->splitline[0], "unsetenv") != 0 &&
		ft_strcmp(shell->splitline[0], "exit") != 0 &&
		ft_access(shell, s) != 0)
		return (0);
	//}
	else
		return (1);
}

int			ft_access(t_shell *shell, char *s)
{
	char	*s2;
	int		i;
	
	i = 0;
	s2 = ft_strnew(ft_strlen(s) + 2);
	ft_strcat(s2, "/");
	ft_strcat(s2, s);
	while (shell->path[i])
	{
		if (access(ft_strjoin(shell->path[i], s2), F_OK | X_OK) == 0)
		{
			shell->exec = ft_strdup(ft_strjoin(shell->path[i], s2));
			return (0);
		}
		i++;
	}
	free(s2);
	return (-1);
}
