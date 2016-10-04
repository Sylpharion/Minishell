/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:31 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:33 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_unsetenv(t_shell *shell)
{
	
	if (!shell->splitline[1])
	{
		ft_putendl("unsetenv: Too few arguments.");
		return ;
	}
	ft_modif_unsetenv(shell);
	if (ft_is_unset(shell) == 0)
		return ;
	ft_delete(shell);
}

void		ft_modif_unsetenv(t_shell *shell)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (shell->splitline[i])
	{
		if (ft_strcmp(shell->splitline[i], "HOME") == 0 && n < 1)
		{
			free(shell->home);
			shell->home = ft_strnew(1);
			n = 1;
			break ;
		}
		else if (ft_strcmp(shell->splitline[i], "PATH") == 0 && n < 1)
		{
			ft_free_tab(shell->path);
			shell->path = (char **)malloc(sizeof(char *) * 2);
			shell->path[0] = ft_strnew(1);
			shell->path[1] = NULL;
			n = 1;
			break ;
		}
		i++;
	}
}

void		ft_delete(t_shell *shell)
{
	char	**update_env;
	int		i;
	int		j;

	i = ft_tablen(shell->env_cpy);
	j = 0;
	update_env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (i < ft_tablen(shell->env_cpy))
	{
		if (ft_verif_unset(shell, shell->env_cpy[i]) == 1)
		{
			update_env[j] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcpy(update_env[j], shell->env_cpy[i]);
			j++;
		}
		i++;
	}
	update_env[j] = NULL;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
}

int			ft_is_unset(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env_cpy[i])
	{
		if (ft_verif_unset(shell, shell->env_cpy[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			ft_verif_unset(t_shell *shell, char *arg)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_cut_arg(arg);
	while (shell->splitline[i])
	{
		if (ft_strcmp(shell->splitline[i], tmp) == 0)
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	free(tmp);
	return (1);
}
