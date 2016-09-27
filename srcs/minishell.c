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

	ft_init(&shell, argc, argv);
	if (env[0])
		ft_parse_env(&shell, env, 0, 0);
	else
		ft_create_env(&shell);
	ft_path(&shell, shell.env_cpy);
	ft_swaggy_prompt();
	ft_loop(&shell);
	return (0);
}

void		ft_loop(t_shell *shell)
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
				ft_exec(shell);
			free(shell->trimline);
			free(shell->line);
			ft_free_tab(shell->splitline);
			ft_swaggy_prompt();
		}
	}
}

void		ft_catch(int sig)
{
	int i;

	i = sig;
	return ;
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
