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

void		ft_exec(t_shell *shell)
{
	if (ft_builtins(shell) == 1)
		return ;
	shell->pid = fork();
	if (shell->pid == 0)
	{
		if (execve(shell->exec, shell->splitline, shell->env_cpy) == -1)
		{
			ft_error(*shell);
			exit(0);
		}
	}
	else
	{
		signal(SIGINT, ft_catch_in_fork);
		wait(NULL);
	}
	free(shell->exec);
}

void		ft_catch_in_fork(int sig)
{
	int i;

	i = sig;
	ft_putchar('\n');
	return ;
}

int			ft_builtins(t_shell *shell)
{
	t_ptr	*ptr;
	char	**tab;
	int		i;

	i = 0;
	ptr = ft_ptr_init();
	tab = ft_tab_init();
	while (ft_strcmp(shell->splitline[0], tab[i]) != 0)
		i++;
	if (ptr[i])
	{
		(ptr[i])(shell);
		free(ptr);
		ft_free_tab(tab);
		return (1);
	}
	else
	{
		free(ptr);
		ft_free_tab(tab);
		return (0);
	}
}

int			ft_isexec(t_shell *shell, char *s)
{
	if (access(shell->splitline[0], F_OK | X_OK) == 0)
	{
		shell->exec = ft_strdup(shell->splitline[0]);
		return (1);
	}
	else if (ft_strcmp(shell->splitline[0], "cd") != 0 &&
		ft_strcmp(shell->splitline[0], "env") != 0 &&
		ft_strcmp(shell->splitline[0], "setenv") != 0 &&
		ft_strcmp(shell->splitline[0], "unsetenv") != 0 &&
		ft_strcmp(shell->splitline[0], "exit") != 0 &&
		ft_strcmp(shell->splitline[0], "echo") != 0 &&
		ft_strcmp(shell->splitline[0], "printenv") != 0 &&
		ft_strcmp(shell->splitline[0], "builtins") != 0 &&
		ft_access(shell, s, 0, NULL) != 0)
		return (0);
	else
		return (1);
}

int			ft_access(t_shell *shell, char *s, int i, char *tmp)
{
	char	*s2;

	if (ft_strncmp(shell->splitline[0], "./", 2) == 0)
	{
		shell->exec = ft_strdup(shell->splitline[0]);
		return (0);
	}
	s2 = ft_strnew(ft_strlen(s) + 2);
	ft_strcat(s2, "/");
	ft_strcat(s2, s);
	while (shell->path[i])
	{
		tmp = ft_strjoin(shell->path[i], s2);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			shell->exec = ft_strdup(tmp);
			free(s2);
			free(tmp);
			return (0);
		}
		free(tmp);
		i++;
	}
	free(s2);
	return (-1);
}

void		ft_builtins_list(t_shell *shell)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_tab_init();
	shell->tab = tab;
	ft_putendl("Builtins list : \n");
	while (i < ft_tablen(tab) - 1)
	{
		ft_putstr("- ");
		ft_putrainbow(tab[i], PURPLE);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
	ft_free_tab(tab);
}
