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

	ft_init(&shell, argv, env);
	//ft_parse_env(&shell, env);
	ft_path(&shell, env);
	ft_swaggy_prompt();
	while (42)
	{
		get_next_line(0, &shell.line);
		if (ft_strlen(shell.line) == 0)
			ft_swaggy_prompt();
	 	else
	 	{
	 		shell.splitline = ft_strsplit(shell.line, ' ');
	 		//ft_parseline(&shell);
	 		if (ft_isexec(&shell, shell.splitline[0]) == 0)
	 			ft_error(shell);
	 		else
	 			ft_exec(shell, shell.splitline[0], env);
	 		ft_swaggy_prompt();
	 	}
	}
	ft_putchar('\n');
	return (0);
}

// void		ft_parseline(t_shell *shell)
// {
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	shell->splitline = ft_strsplit(shell->line, ' ');
// 	while (shell->splitline[i])
// 		i++;
// 	shell->argline = (char **)malloc(sizeof(char *) * i);
// 	i = 1;
// 	while (shell->splitline[i])
// 	{
// 		shell->argline[j] = ft_strnew(ft_strlen(shell->splitline[i]));
// 		ft_strcpy(shell->argline[j], shell->splitline[i]);
// 		i++;
// 	}
// }

void		ft_error(t_shell shell)
{
	ft_putstr("minishell: command not found: ");
	ft_putendl(shell.splitline[0]);
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
	// int j = 0;
	// char **tab = (char **)malloc(sizeof(char *) * ft_tablen(shell.path)); 
	// while (shell.path[j])
	// {
	// 	tab[j] = ft_strjoin(shell.path[j], shell.splitline[0]);
	// 	j++;
	// }



	shell.pid = fork();
	//j = 0;
	if (shell.pid == 0)
	{
		execve(shell.exec, shell.splitline, env);
		// ft_putrainbow("***fake ", PURPLE);
		// ft_putrainbow(cmd, PURPLE);
		// ft_putrainbow("***", PURPLE);
		// ft_putchar('\n');
		//exit(0);
	}
	else if (shell.pid > 0)
		wait(NULL);

	/* execve */

	// if (ft_strcmp(shell.splitline[0], "env") == 0)
	// {
	// 	int	ii = 0;
	// 	while(shell.env_cpy[ii])
	// 	{
	// 		ft_putendl(shell.env_cpy[ii]);
	// 		ii++;
	// 	}
	// }
}

void		ft_path(t_shell *shell, char *env[])
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
	s2 = ft_strnew(ft_strlen(s));
	while (s[i] != '=')
		i++;
	i++;
	while (s[i])
	{
		s2[j] = s[i];
		j++;
		i++;
	}
	shell->path = ft_strsplit(s2, ':');
}

void		ft_init(t_shell *shell, char **argv, char *env[])
{
	shell->line = NULL;
	shell->path = NULL;
	shell->splitline = NULL;
	shell->exec = NULL;
	shell->env_cpy = env;
}

void		ft_parse_env(t_shell *shell, char *env[])
{
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	 while (env[i])
	{
	 	if (ft_strlen(env[i]) > j)
	 		j = ft_strlen(env[i]);
		i++;
		n++;
	}
	shell->env_cpy = (char **)malloc(sizeof(char*) * i + 1);
	i = 0;
	while (i < n)
	{
	 	shell->env_cpy[i] = ft_strnew(j);
	 	ft_strcpy(shell->env_cpy[i], env[i]);
	 	i++;
	}
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
	if (/*ft_strcmp(shell->splitline[0], "cd") != 0 &&
		ft_strcmp(shell->splitline[0], "env") != 0 &&
		ft_strcmp(shell->splitline[0], "setenv") != 0 &&
		ft_strcmp(shell->splitline[0], "unsetenv") != 0 &&
		ft_strcmp(shell->splitline[0], "exit") != 0 &&*/
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
	s2 = ft_strnew(ft_strlen(s) + 1);
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
	return (-1);
}
