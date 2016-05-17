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
	pid_t	pid;
	char	*line;
	char	**splitline;
	t_shell	shell;

	line = NULL;
	splitline = NULL;
	ft_init(&shell, env);
	ft_swaggy_prompt();
	while (42)
	{
		get_next_line(0, &line);
		if (ft_strlen(line) == 0)
			ft_swaggy_prompt();
		else
		{
			splitline = ft_strsplit(line, ' ');
			if (ft_isexec(splitline) == 0)
			{
				ft_putstr("minishell: command not found: ");
				ft_putendl(splitline[0]);
			}
			else
				// pid = fork();
				// if (pid == 0)
				// 	exit (0);
				// else if (pid > 0)
				// 	wait(NULL);
				/* execve */
				if (ft_strcmp(splitline[0], "env") == 0)
				{
					int	ii = 0;
					while(shell.env_cpy[ii])
					{
						ft_putendl(shell.env_cpy[ii]);
						ii++;
					}
				}
				ft_swaggy_prompt();
		}
	}
	ft_putchar('\n');
	return (0);
}

void		ft_init(t_shell *shell, char *env[])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strlen(env[i]) > j)
			j = ft_strlen(env[i]);
		i++;
	}
	shell->env_cpy = (char **)malloc(sizeof(char*) * i + 1);
	shell->env_cpy[i] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		shell->env_cpy[i] = ft_strnew(j + 1);
		shell->env_cpy[i] = ft_strdup(env[i]);
		shell->env_cpy[i][ft_strlen(shell->env_cpy[i])] = 0;
		i++;
	}
}

void		ft_swaggy_prompt(void)
{
	ft_putrainbow("MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL]", YELLOW);
	ft_putrainbow(" $> ", GREEN);
}

int			ft_isexec(char **line)
{
	if (ft_strcmp(line[0], "cd") != 0 &&
		ft_strcmp(line[0], "ls") != 0 &&
		ft_strcmp(line[0], "env") != 0 &&
		ft_strcmp(line[0], "setenv") != 0 &&
		ft_strcmp(line[0], "unsetenv") != 0 &&
		ft_strcmp(line[0], "exit") != 0)
		return (0);
	else
		return (1);
}
