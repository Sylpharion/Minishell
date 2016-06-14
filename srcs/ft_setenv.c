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
		update_env = ft_ft_setenv(shell, update_env);
	free(shell->env_cpy);
	shell->env_cpy = update_env;
}

char		**ft_ft_setenv(t_shell *shell, char **update_env)
{
	int		i;
	int		verif;

	i = 0;
	verif = 0;
	update_env = (char **)malloc(sizeof(char *) * ft_tablen(shell->env_cpy) + 10);
	while (shell->env_cpy[i])
	{
		if (ft_strcmp(shell->splitline[1], ft_cut_arg(shell->env_cpy[i])) == 0 && verif == 0)
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
	update_env[i] = NULL;
	return (update_env);
}

char		*ft_add_env(t_shell *shell)
{
	char	*str;

	str = NULL;
	if (ft_tablen(shell->splitline) == 3)
	{
		str = ft_strnew(ft_strlen(shell->splitline[1]) + ft_strlen(shell->splitline[2]) + 2);
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