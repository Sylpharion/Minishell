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
		ft_parse_env(&shell, env, 0, 0);
	else
		ft_create_env(&shell);
	ft_path(&shell, shell.env_cpy);
	ft_swaggy_prompt();
	ft_loop(&shell);
	return (0);
}

void		ft_loop(t_shell	*shell)
{
	while (42)
	{
		signal(SIGINT, ft_catch);
		shell->line = ft_get_the_line();
		shell->trimline = ft_strtrim(shell->line);
		shell->splitline = ft_strsplit(shell->trimline, ' ');
		if (!shell->splitline[0])
		{
			free(shell->trimline);
	 		free(shell->line);
	 		ft_free_tab(shell->splitline);
			ft_swaggy_prompt();
		}
	 	else
	 	{
		 	if (ft_isexec(shell, shell->splitline[0]) == 0)
		 		ft_error(*shell);
		 	else
			 	ft_exec(shell, shell->splitline[0], shell->env_cpy);
			free(shell->trimline);
	 		free(shell->line);
	 		ft_free_tab(shell->splitline);
	 		ft_swaggy_prompt();
	 	}
	}
}

void		ft_catch(int sig)
{
	return ;
}

char		*ft_get_the_line(void)
{
	char	*str;
	int		ret;

	str = ft_strnew(BOEUF_SIZE + 1);
	str[BOEUF_SIZE] = 0;
	ret = read(0, str, BOEUF_SIZE);
	return (str);
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

int			ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void		ft_swaggy_prompt(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_putrainbow("[MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL] ", YELLOW);
	ft_putrainbow(tmp, GREEN);
	ft_putrainbow(" ➤ ", GREEN);
	free(tmp);
}
