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

void		ft_free_setenv(t_shell *shell, char **update_env)
{
	int		i;
	char	*tmp;

	if (ft_tablen(update_env) > 0)
		ft_free_setenv_plus(shell, update_env);
	i = 0;
	while (shell->env_cpy[i] && ft_strcmp(shell->splitline[0], "setenv") == 0)
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
	shell->env_cpy = (char **)malloc(sizeof(char *)	* ft_tablen(update_env) + 1);
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

	/* verif */

	i = 0;
	verif = 0;
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

	/* maj tab */

	if (verif == 1)
	{
		i = 0;
		while (shell->env_cpy[i])
		{
			tmp = ft_cut_arg(shell->env_cpy[i]);
			if (ft_strcmp(shell->splitline[1], tmp) == 0)
			{
				free(tmp);
				break ;
			}
			free(tmp);
			i++;
		}
		free(shell->env_cpy[i]);
		shell->env_cpy[i] = ft_add_env(shell);
		i = 0;
		update_env = (char **)malloc(sizeof(char *)
					* ft_tablen(shell->env_cpy) + 10);
		while (shell->env_cpy[i])
		{
			update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcat(update_env[i], shell->env_cpy[i]);
			i++;
		}
		update_env[i] = NULL;
	}

	/* new tab */

	else
	{
		i = 0;
		update_env = (char **)malloc(sizeof(char *)
					* ft_tablen(shell->env_cpy) + 20);
		while (shell->env_cpy[i])
		{
			update_env[i] = ft_strnew(ft_strlen(shell->env_cpy[i]));
			ft_strcat(update_env[i], shell->env_cpy[i]);
			i++;
		}
		update_env[i] = ft_add_env(shell);
		update_env[i + 1] = NULL;
	}
	return (update_env);
}

char		*ft_add_env(t_shell *shell)
{
	char	*str;
	char	*str2;
	char	*tmp;

	str = NULL;
	if (ft_tablen(shell->splitline) == 3)
	{
		str = ft_strnew(ft_strlen(shell->splitline[1]) +
				ft_strlen(shell->splitline[2]) + 2);
		ft_strcat(str, shell->splitline[1]);
		ft_strcat(str, "=");
		ft_strcat(str, shell->splitline[2]);
	}
	else if (ft_tablen(shell->splitline) == 2)
	{
		tmp = ft_strjoin(shell->splitline[1], "=");
		str = ft_strnew(ft_strlen(shell->splitline[1]) + 2);
		ft_strcat(str, tmp);
		free(tmp);
	}
	str2 = ft_strdup(str);
	free(str);
	return (str2);
}