/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:24:04 by smassand          #+#    #+#             */
/*   Updated: 2016/09/27 18:24:12 by smassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_maj_setenv(t_shell *shell, char *tmp, int i,
							char **update_env)
{
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
	return (update_env);
}

char		**ft_new_setenv(t_shell *shell, int i, char **update_env)
{
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
