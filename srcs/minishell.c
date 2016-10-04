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
		shell->line = ft_parseline(shell);
		shell->splitline = ft_strsplit(shell->line, ' ');
		shell->splitline = ft_trimline(shell);
		if (ft_tablen(shell->splitline) < 1)
		{
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
			free(shell->line);
			ft_free_tab(shell->splitline);
			ft_swaggy_prompt();
		}
	}
}

char		*ft_parseline(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(shell->line) + 1);
	while (shell->line[i])
	{
		if (shell->line[i] != '\t')
		{
			tmp[j] = shell->line[i];
			j++;
		}
		i++;
	}
	tmp[j] = 0;
	free(shell->line);
	return (tmp);
}

char		*ft_parsetild(t_shell *shell, char *line, int i, int j)
{
	char	*tmp_line;

	if (line[0] != '~')
		return (line);
	tmp_line = (char *)malloc(sizeof(char) * ft_strlen(shell->line) +
											ft_strlen(shell->home) + 1);
	while (line[i])
	{
		if (line[0] == '~' && line[1] != '~' && i == 0)
		{
			ft_strcat(tmp_line, shell->home);
			j = ft_strlen(tmp_line);
			i++;
		}
		else
		{
			tmp_line[j] = line[i];
			j++;
			i++;
		}
	}
	tmp_line[j] = 0;
	free(line);
	return (tmp_line);
}

char		**ft_trimline(t_shell *shell)
{
	int		i;
	char	**splitline;

	i = 0;
	splitline = (char **)malloc(sizeof(char *) *
					ft_tablen(shell->splitline) + 1);
	while (shell->splitline[i])
	{
		splitline[i] = ft_strtrim(shell->splitline[i]);
		splitline[i] = ft_parsetild(shell, splitline[i], 0, 0);
		i++;
	}
	splitline[i] = NULL;
	ft_free_tab(shell->splitline);
	return (splitline);
}

void		ft_swaggy_prompt(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_putrainbow("[MY", RED);
	ft_putrainbow("_SWAGGY_", BLUE);
	ft_putrainbow("SHELL] ", YELLOW);
	if (tmp)
		ft_putrainbow(tmp, GREEN);
	ft_putrainbow(" ➤ ", GREEN);
	free(tmp);
}
