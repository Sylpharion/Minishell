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

// leaks sur strtrim  et split 
	ft_init(&shell, argv);
	if (env[0])
		ft_parse_env(&shell, env);
	else
		ft_create_env(&shell);
	ft_path(&shell, shell.env_cpy);
	ft_swaggy_prompt();
	 while (42)
	{
		shell.line = ft_get_the_line();
		shell.splitline = ft_strsplit(ft_strtrim(shell.line), ' ');
		if (!shell.splitline[0])
			ft_swaggy_prompt();
	 	else
	 	{
		 	if (ft_isexec(&shell, shell.splitline[0]) == 0)
		 		ft_error(shell);
		 	else
			 	ft_exec(&shell, shell.splitline[0], shell.env_cpy);
	 		ft_swaggy_prompt();
	 	}
	 	free(shell.line);
	}
	return (0);
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
	// if (stat(shell.exec, &shell.st) == -1)
	// {
	// 	ft_putstr("minishell: no such file or directory: ");
	// 	ft_putendl(s);
	// }
	// else if (access(shell.exec, F_OK) == 0 && access(shell.exec, X_OK) == -1)
	// {
	// 	ft_putstr("minishell: permission denied: ");
	// 	ft_putendl(s);
	// }
	// else
	// {
		ft_putstr("minishell: command not found: ");
		ft_putendl(shell.splitline[0]);
	//}
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
