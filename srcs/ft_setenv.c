/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:48:20 by smassand          #+#    #+#             */
/*   Updated: 2016/06/01 14:48:24 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setenv(t_shell *shell)
{
	char	**update_env;

	update_env = NULL;
	if (ft_tablen(shell->splitline) < 2)
	{
		ft_env(shell);
		return ;
	}
	else if (ft_tablen(shell->splitline) > 3)
		ft_putendl("setenv: Too many arguments.");
	else
		update_env = ft_update_setenv(shell);
	ft_free_setenv(shell, update_env);
}

// void		ft_modif_setenv(t_shell *shell)
// {
// 	return ;
// }

void		ft_free_setenv(t_shell *shell, char **update_env)
{
	int		i;
	char	*tmp;

	if (ft_tablen(update_env) > 0)
		ft_free_setenv_plus(shell, update_env);
	i = 0;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp("PATH", tmp) == 0)
		{
			ft_free_tab(shell->path);
			ft_path(shell, shell->env_cpy);
			free(tmp);
			return ;
		}
		free(tmp);
		i++;
	}
}

void		ft_free_setenv_plus(t_shell *shell, char **update_env)
{
	int		i;

	i = 0;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = (char **)malloc(sizeof(char *)
						* ft_tablen(update_env) + 1);
	while (update_env[i])
	{
		shell->env_cpy[i] = ft_strnew(ft_strlen(update_env[i]));
		ft_strcpy(shell->env_cpy[i], update_env[i]);
		i++;
	}
	shell->env_cpy[i] = NULL;
	ft_free_tab(update_env);
}

char		**ft_update_setenv(t_shell *shell)
{
	int		i;
	int		verif;
	char	**update_env;
	char	*tmp;

	i = 0;
	verif = 0;
	update_env = NULL;
	while (shell->env_cpy[i])
	{
		tmp = ft_cut_arg(shell->env_cpy[i]);
		if (ft_strcmp(shell->splitline[1], tmp) == 0)
		{
			verif = 1;
			free(tmp);
			break ;
		}
		free(tmp);
		i++;
	}
	if (verif == 1)
		update_env = ft_maj_setenv(shell, tmp, 0, update_env);
	else
		update_env = ft_new_setenv(shell, 0, update_env);
	return (update_env);
}
