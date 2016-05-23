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

	ft_init(&shell);
	ft_parse_env(&shell, env);
	ft_path(&shell);
	ft_swaggy_prompt();
	while (42)
	{
		get_next_line(0, &shell.line);
		if (ft_strlen(shell.line) == 0)
			ft_swaggy_prompt();
		else
		{
			shell.splitline = ft_strsplit(shell.line, ' ');
			if (ft_isexec(shell) == 0)
				ft_error(shell);
			else
				ft_exec(shell);
			ft_swaggy_prompt();
		}
	}
	ft_putchar('\n');
	return (0);
}

void		ft_error(t_shell shell)
{
	ft_putstr("minishell: command not found: ");
	ft_putendl(shell.splitline[0]);
}

void		ft_exec(t_shell shell)
{
	// shell.pid = fork();
	// if (pid == 0)
	// 	exit (0);
	// else if (pid > 0)
	// 	wait(NULL);
	/* execve */
	if (ft_strcmp(shell.splitline[0], "env") == 0)
	{
		int	ii = 0;
		while(shell.env_cpy[ii])
		{
			ft_putendl(shell.env_cpy[ii]);
			ii++;
		}
	}
}

int			ft_access(t_shell *shell)
{

}

void		ft_path(t_shell *shell);
{

}

void		ft_init(t_shell *shell)
{
	shell->line = NULL;
	shell->path = NULL;
	shell->splitline = NULL;
	shell->env_cpy = NULL;
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
	ft_putrainbow("MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL]", YELLOW);
	ft_putrainbow(" <[O_O]> ", GREEN);
}

int			ft_isexec(t_shell *shell)
{
	if (ft_strcmp(shell->splitline[0], "cd") != 0 &&
		ft_strcmp(shell->splitline[0], "env") != 0 &&
		ft_strcmp(shell->splitline[0], "setenv") != 0 &&
		ft_strcmp(shell->splitline[0], "unsetenv") != 0 &&
		ft_strcmp(shell->splitline[0], "exit") != 0 &&
		/*ft_access(shell) != 0*/)
		return (0);
	else
		return (1);
}


