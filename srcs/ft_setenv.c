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
		ft_printenv(shell);
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

	i = 0;
	ft_free_tab(shell->env_cpy);
	shell->env_cpy = update_env;
	while (shell->env_cpy[i])
	{
		if (ft_strcmp(shell->splitline[1], ft_cut_arg(shell->env_cpy[i])) == 0)
		{
			ft_path(shell, shell->env_cpy);
			return ;
		}
		i++;
	}
}

char		**ft_update_setenv(t_shell *shell)
{
	int		i;
	int		verif;
	char	**update_env;

	i = 0;
	verif = 0;
	// verifer si la variable existe avant de malloc
	// if existe while (env_cpy[i])
	// if ft_strncmp(env_cpy[i], splitline[1], ft_strlen(splitline[i])) 
	// a verifer si il ne peut pas fair une erreur "path=" != "pathique=" il faut pas que ca marche 
	// free(env_cpy[i]);
	// env_cpy[i] = malloc(sizeof(char) * taille arg1 + arg2 + '=' + 1)
	// else 
	// malloc + 1
	// et rajoute 

	while (shell->env_cpy[i])
	{
		if (ft_strcmp(shell->splitline[1], ft_cut_arg(shell->env_cpy[i])) == 0)
		{
			free(shell->env_cpy[i]);
			shell->env_cpy[i] = ft_add_env(shell);
			verif = 1;
			break ;
		}
		else
			verif = 0;
		i++;
	}
	if (verif == 1)
		return (shell->env_cpy);
	else
	{
		update_env = (char **)malloc(sizeof(char *) *
					ft_tablen(shell->env_cpy) + 2);
		i = 0;
		while (shell->env_cpy[i])
		{
			update_env[i] = ft_strdup(shell->env_cpy[i]);
			i++;
		}
		update_env[i] = ft_add_env(shell);
		update_env[i + 1] = NULL;
	}
	/* 

	while (shell->env_cpy[i])
	{
		if (ft_strcmp(shell->splitline[1], ft_cut_arg(shell->env_cpy[i]))
						== 0 && verif == 0)
		{
			update_env[i] = ft_add_env(shell);	
			verif = 1;
		}
		else
			update_env[i] = ft_strdup(shell->env_cpy[i]);
		i++;
	}
	if (verif == 0)
		update_env[i] = ft_add_env(shell);
	i = 0;
	while (update_env[i])
		i++;
	update_env[i] = NULL;*/
	return (update_env);
}

char		*ft_add_env(t_shell *shell)
{
	char	*str;

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
		str = ft_strnew(ft_strlen(shell->splitline[1]) + 2);
		str = ft_strjoin(shell->splitline[1], "=");
	}
	return (str);
}