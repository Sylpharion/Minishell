/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:25:04 by smassand          #+#    #+#             */
/*   Updated: 2016/05/11 15:25:48 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			main(int argc, char **argv, char *env[])
{
	t_shell	shell;

	ft_init(&shell, argv);
	if (env[0])
		ft_parse_env(&shell, env);
	else
		ft_create_env(&shell);
	ft_path(&shell, shell.env_cpy);
	ft_swaggy_prompt();
	while (42)
	{
		get_next_line(0, &shell.line);
		if (ft_strlen(shell.line) == 0)
			ft_swaggy_prompt();
	 	else
	 	{
	 		shell.splitline = ft_strsplit(shell.line, ' ');
	 		if (ft_isexec(&shell, shell.splitline[0]) == 0)
	 			ft_error(shell);
	 		else
	 			ft_exec(shell, shell.splitline[0], shell.env_cpy);
	 		ft_swaggy_prompt();
	 	}
	}
	ft_putchar('\n');
	return (0);
}

void		ft_error(t_shell shell)
{
	if (shell.splitline[0][0] == '/')
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(shell.splitline[0]);
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(shell.splitline[0]);
	}
}

int			ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void		ft_exec(t_shell shell, char *cmd, char *env[])
{
	t_ptr	*ptr;
	char	**tab;
	int		i;

	i = 0;
	shell.pid = fork();
	if (shell.pid == 0)
	{
		ptr = ft_ptr_init();
		tab = ft_tab_init();
		while (ft_strcmp(shell.splitline[0], tab[i]) != 0)
			i++;
		if (ptr[i])
			(*ptr[i])(shell);
		else if (execve(shell.exec, shell.splitline, shell.env_cpy) == -1)
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(shell.splitline[0]);
			free(shell.exec);
			exit(0);
		}
	}
	else if (shell.pid > 0)
		wait(NULL);
}

t_ptr		*ft_ptr_init(void)
{
	t_ptr	*ptr;

	ptr = malloc(sizeof(&ptr) * 6);
	ptr[0] = ft_env;
	ptr[1] = ft_setenv;
	ptr[2] = ft_unsetenv;
	ptr[3] = ft_cd;
	ptr[4] = ft_exit;
	ptr[5] = NULL;
	return (ptr);
}

char		**ft_tab_init(void)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 6);
	tab[0] = ft_strdup("env");
	tab[1] = ft_strdup("setenv");
	tab[2] = ft_strdup("unsetenv");
	tab[3] = ft_strdup("cd");
	tab[4] = ft_strdup("exit");
	tab[5] = NULL;
	return (tab);
}

void		ft_path(t_shell *shell, char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (strncmp(env[i], "PATH", 4) != 0)
		i++;
	s = ft_strnew(ft_strlen(env[i]) + 1);
	ft_strcpy(s, env[i]);
	ft_parse_path(shell, s);
}

void		ft_parse_path(t_shell *shell, char *s)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s[i] != '=')
		i++;
	i++;
	s2 = ft_strnew(ft_strlen(s) - i);
	while (s[i])
	{
		s2[j] = s[i];
		j++;
		i++;
	}
	free(s);
	shell->path = ft_strsplit(s2, ':');
	free(s2);
}

void		ft_init(t_shell *shell, char **argv)
{
	shell->line = NULL;
	shell->path = NULL;
	shell->splitline = NULL;
	shell->exec = NULL;
	shell->env_cpy = NULL;
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

	getcwd(str, 255);
	shell->env_cpy = (char **)malloc(sizeof(char *) * 8);
	shell->env_cpy[0] = ft_strdup("HOME=/nfs/2014/s/smassand");
	shell->env_cpy[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	shell->env_cpy[2] = ft_strdup("LOGNAME=smassand");
	shell->env_cpy[3] = ft_strdup("SHLVL=1");
	shell->env_cpy[4] = ft_strdup(ft_strjoin("PWD=", str));
	shell->env_cpy[5] = ft_strdup(ft_strjoin("OLDPWD=", str));
	shell->env_cpy[6] = ft_strdup("_=/usr/bin/env");
	shell->env_cpy[7] = NULL;
}

void		ft_swaggy_prompt(void)
{
	ft_putrainbow("[MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL]", YELLOW);
	ft_putrainbow(" ➤ ", GREEN);
}

int			ft_isexec(t_shell *shell, char *s)
{
	if (ft_strcmp(shell->splitline[0], "cd") != 0 &&
		ft_strcmp(shell->splitline[0], "env") != 0 &&
		ft_strcmp(shell->splitline[0], "setenv") != 0 &&
		ft_strcmp(shell->splitline[0], "unsetenv") != 0 &&
		ft_strcmp(shell->splitline[0], "exit") != 0 &&
		ft_access(shell, s) != 0)
		return (0);
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

void		ft_setenv(t_shell shell)
{
	ft_putrainbow("✗✗✗ fake setenv ✗✗✗\n", PURPLE);
	exit(0);
}

void		ft_unsetenv(t_shell shell)
{
	ft_putrainbow("✗✗✗ fake unsetenv ✗✗✗\n", PURPLE);
	exit(0);
}

void		ft_cd(t_shell shell)
{
	ft_putrainbow("✗✗✗ fake cd ✗✗✗\n", PURPLE);
	exit(0);
}

void		ft_exit(t_shell shell)
{
	ft_putrainbow("✗✗✗ fake exit ✗✗✗\n", PURPLE);
	exit(0);
}
