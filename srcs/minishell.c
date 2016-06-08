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
		shell.splitline = ft_strsplit(ft_strtrim(shell.line), ' ');
		if (!shell.splitline[0])
			ft_swaggy_prompt();
	 	else
	 	{
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

void		ft_swaggy_prompt(void)
{
	ft_putrainbow("[MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL]", YELLOW);
	ft_putrainbow(" ➤ ", GREEN);
}
